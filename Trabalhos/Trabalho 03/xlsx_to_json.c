#include <xlsxwriter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

void write_cell(json_t *json, lxw_cell *cell) {
    switch (cell->type) {
        case LXW_CELL_NUMBER:
            json_object_set_new(json, "value", json_real(cell->u.number));
            break;
        case LXW_CELL_STRING:
            json_object_set_new(json, "value", json_string(cell->u.string));
            break;
        case LXW_CELL_BOOLEAN:
            json_object_set_new(json, "value", json_boolean(cell->u.boolean));
            break;
        case LXW_CELL_ERROR:
            json_object_set_new(json, "value", json_string("ERROR"));
            break;
        default:
            json_object_set_new(json, "value", json_string(""));
            break;
    }
}

int main() {
    lxw_workbook  *workbook  = workbook_new("Precos.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    /* Write some data to the worksheet. */
    worksheet_write_string(worksheet, 0, 0, "Name", NULL);
    worksheet_write_string(worksheet, 0, 1, "Age", NULL);
    worksheet_write_string(worksheet, 1, 0, "John Smith", NULL);
    worksheet_write_number(worksheet, 1, 1, 35, NULL);
    worksheet_write_string(worksheet, 2, 0, "Jane Doe", NULL);
    worksheet_write_number(worksheet, 2, 1, 29, NULL);

    /* Iterate over the rows and columns to create a JSON object. */
    json_t *json = json_object();
    json_t *data = json_array();
    for (lxw_row_t row_num = 0; row_num <= worksheet->dim.row_max; row_num++) {
        json_t *row = json_object();
        for (lxw_col_t col_num = 0; col_num <= worksheet->dim.col_max; col_num++) {
            lxw_cell *cell = lxw_get_cell(worksheet, row_num, col_num);
            if (cell) {
                json_t *col = json_object();
                json_object_set_new(col, "type", json_string(lxw_get_cell_format_name(cell)));
                write_cell(col, cell);
                json_object_set_new(row, lxw_col_to_name(col_num), col);
            }
        }
        json_array_append_new(data, row);
    }
    json_object_set_new(json, "data", data);

    /* Write the JSON object to a file. */
    FILE *file = fopen("example.json", "w");
    fprintf(file, "%s", json_dumps(json, 0));
    fclose(file);

    /* Clean up. */
    json_decref(json);
    workbook_close(workbook);

    return 0;
}
