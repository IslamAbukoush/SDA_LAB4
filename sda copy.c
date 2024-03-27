#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER 100

typedef struct {
    unsigned int day;
    unsigned int month;
    unsigned int year;
} Date;

typedef struct {
    float tons;
    float kg;
    float grams;
} Mass;

typedef struct {
    char* commodity_name;
    char* manufacturer;
    Date contract_conclusion_date;
    union
    {
        unsigned int unit_price_int;
        float unit_price_float;
    };
    
    union
    {
        unsigned int wholesale_price_int;
        float wholesale_price_float;
    };
    
    Mass quantity;
} Food_Goods;

void print_food_goods(Food_Goods entry, int isFloat);
void print_food_goods_arr(Food_Goods* arr, int n, int isFloat);
void swap_food_goods(Food_Goods* a, Food_Goods* b);
int partition_by_commodity_name(Food_Goods* arr, int low, int high);
void quick_sort_by_commodity_name(Food_Goods* arr, int low, int high);
int partition_by_wholesale_price(Food_Goods* arr, int low, int high, int isFloat);
void quick_sort_by_wholesale_price(Food_Goods *arr, int low, int high, int isFloat);
int partition_by_unit_price(Food_Goods* arr, int low, int high, int isFloat);
void quick_sort_by_unit_price(Food_Goods *arr, int low, int high, int isFloat);
void counting_sort_by_commodity_name(Food_Goods* arr, int n);
void counting_sort_by_wholesale_price(Food_Goods* arr, int n, int isFloat);
void counting_sort_by_unit_price(Food_Goods* arr, int n, int isFloat);


int main() {
    srand(time(NULL));
    int isFloat = 0;
    char* commodities[] = {
        "Chronium Fiber",
        "Solarite Crystals",
        "Lumino Alloy",
        "Quantum Dust",
        "Electrum Ore",
        "Hyperium Gas",
        "Nova Plasma",
        "Titanite Shard",
        "Nebulae Essence",
        "Arcane Resin"
    };

    char* manufacturers[] = {
        "AetherTech Industries",
        "Quantum Dynamics Corporation",
        "Celestial Innovations",
        "Nebula Nexus Enterprises",
        "Stellar Solutions Ltd.",
        "Fusion Forge Technologies",
        "Infinity Manufacturing Co.",
        "Galactic Innovations Group",
        "Cosmos Creations Inc.",
        "Astral Engineering Solutions"
    };

    printf("Enter the number of entries: ");
    int n;
    scanf("%i", &n);
    Food_Goods* entries = (Food_Goods*)malloc(sizeof(Food_Goods)*n);

    printf("Manual(0) or Random(1) generation? ");
    int option;
    scanf("%i", &option);
    printf("Do you wish to use floats or ints for prices? (0- int | 1- float)");
    scanf("%i", &isFloat);

    if (option) {
        for (int i = 0; i < n; i++) {
            free(entries[i].commodity_name);
            free(entries[i].manufacturer);

            Food_Goods temp_entry;
            temp_entry.commodity_name = malloc(sizeof(char) * (strlen(commodities[rand() % 10]) + 1));
            strcpy(temp_entry.commodity_name, commodities[rand() % 10]);
            temp_entry.manufacturer = malloc(sizeof(char) * (strlen(manufacturers[rand() % 10]) + 1));
            strcpy(temp_entry.manufacturer, manufacturers[rand() % 10]);
            temp_entry.contract_conclusion_date.day = rand() % 31 + 1;
            temp_entry.contract_conclusion_date.month = rand() % 12 + 1;
            temp_entry.contract_conclusion_date.year = 1999 + rand() % 25;
            if(isFloat) {
                temp_entry.wholesale_price_float =(rand() % 99999)+1;
                temp_entry.unit_price_float = (rand() % 999)+1;
            } else {
                temp_entry.wholesale_price_int =(rand() % 99999)+1;
                temp_entry.unit_price_int = (rand() % 999)+1;
            }
            temp_entry.quantity.tons = (float)(rand() % 150);
            temp_entry.quantity.kg = (float)(rand() % 1000);
            temp_entry.quantity.grams = (float)(rand() % 150);
            entries[i] = temp_entry;
        }
    } else {
        for(int i = 0; i < n; i++) {
            Food_Goods temp_entry;
            printf("Enter the commodity name: ");
            temp_entry.commodity_name = (char*)malloc(sizeof(char)*BUFFER);
            scanf("%s", temp_entry.commodity_name);
            printf("Enter the manufacturer name: ");
            temp_entry.manufacturer = (char*)malloc(sizeof(char)*BUFFER);
            scanf("%s", temp_entry.manufacturer);
            printf("Enter the contract conclusion date: \n");
            printf("Day: ");
            scanf("%d", &temp_entry.contract_conclusion_date.day);
            printf("Month: ");
            scanf("%d", &temp_entry.contract_conclusion_date.month);
            printf("Year: ");
            scanf("%d", &temp_entry.contract_conclusion_date.year);
            printf("Enter wholesale price: ");
            if(isFloat) {
                scanf("%f", &temp_entry.wholesale_price_float);
            } else {
                scanf("%i", &temp_entry.wholesale_price_int);
            }
            printf("Enter unit price: ");
            if(isFloat) {
                scanf("%f", &temp_entry.unit_price_float);
            } else {
                scanf("%i", &temp_entry.unit_price_int);
            }
            printf("Enter quantity:\n");
            printf("Tons: ");
            scanf("%f", &temp_entry.quantity.tons);
            printf("Kilograms: ");
            scanf("%f", &temp_entry.quantity.kg);
            printf("Grams: ");
            scanf("%f", &temp_entry.quantity.grams);
            entries[i] = temp_entry;
        }
    }
    while(1) {
        printf("--------------Menu--------------\n");
        printf("| 0- Exit.                     |\n");
        printf("| 1- Print entries.            |\n");
        printf("| 2- Sort entries.             |\n");
        printf("| 3- Modify entries.           |\n");
        printf("--------------------------------\n");
        int choice;
        scanf("%i", &choice);
        switch (choice)
        {
            case 1:
                print_food_goods_arr(entries, n, isFloat);
                break;
            case 2:
                printf("-------------------Menu-----------------\n");
                printf("| 1- Quick sort by commodity name.     |\n");
                printf("| 2- Quick sort by wholesale price.    |\n");
                printf("| 3- Quick sort by unit price.         |\n");
                printf("| 4- Counting sort by commodity name.  |\n");
                printf("| 5- Counting sort by wholesale price. |\n");
                printf("| 6- Counting sort by unit price.      |\n");
                printf("----------------------------------------\n");
                int alg = 1;
                scanf("%i", &alg);
                switch(alg)
                {
                    case 1:
                        quick_sort_by_commodity_name(entries, 0, n - 1);
                        printf("Entries sorted by commodity name.\n");
                        break;
                    case 2:
                        quick_sort_by_wholesale_price(entries, 0, n - 1, isFloat);
                        printf("Entries sorted by wholesale price.\n");
                        break;
                    case 3:
                        quick_sort_by_unit_price(entries, 0, n - 1, isFloat);
                        printf("Entries sorted by unit price.\n");
                        break;
                    case 4:
                        counting_sort_by_commodity_name(entries, n);
                        printf("Entries sorted by commodity name using counting sort.\n");
                        break;
                    case 5:
                        counting_sort_by_wholesale_price(entries, n, isFloat);
                        printf("Entries sorted by wholesale price using counting sort.\n");
                        break;
                    case 6:
                        counting_sort_by_unit_price(entries, n, isFloat);
                        printf("Entries sorted by unit price using counting sort.\n");
                        break;
                    default:
                        exit(0);
                }
                break;
            case 3:
                int entryIndex;
                printf("Enter the index of the entry that you would like to change: ");
                scanf("%i", &entryIndex);
                printf("---------What to modify---------\n");
                printf("| 0- Exit.                     |\n");
                printf("| 1- Commodity name.           |\n");
                printf("| 2- Manufacturer name.        |\n");
                printf("| 3- Contract conclusion date. |\n");
                printf("| 4- Wholesale price.          |\n");
                printf("| 5- Unit price.               |\n");
                printf("| 6- Quantity.                 |\n");
                printf("--------------------------------\n");
                int mod = 1;
                scanf("%i", &mod);
                switch (mod)
                {
                    case 1:
                        free(entries[entryIndex].commodity_name);
                        entries[entryIndex].commodity_name = (char*)malloc(sizeof(char)*BUFFER);
                        scanf("%s", entries[entryIndex].commodity_name);
                        break;
                    case 2:
                        free(entries[entryIndex].manufacturer);
                        entries[entryIndex].manufacturer = (char*)malloc(sizeof(char)*BUFFER);
                        scanf("%s", entries[entryIndex].manufacturer);
                        break;
                    case 3:
                        printf("Enter the contract conclusion date: \n");
                        printf("Day: ");
                        scanf("%d", &entries[entryIndex].contract_conclusion_date.day);
                        printf("Month: ");
                        scanf("%d", &entries[entryIndex].contract_conclusion_date.month);
                        printf("Year: ");
                        scanf("%d", &entries[entryIndex].contract_conclusion_date.year);
                        break;
                    case 4:
                        printf("Do you want to enter the wholesale price in integers or in floats? (0- int | 1- float)");
                        int type = 0;
                        scanf("%i", &type);
                        printf("Enter wholesale price: ");
                        if(type) {
                            scanf("%f", &entries[entryIndex].wholesale_price_float);
                        } else {
                            scanf("%i", &entries[entryIndex].wholesale_price_int);
                        }
                        break;
                    case 5:
                        printf("Do you want to enter the unit price in integers or in floats? (0- int | 1- float)");
                        int type2 = 0;
                        scanf("%i", &type2);
                        printf("Enter unit price: ");
                        if(type2) {
                            scanf("%f", &entries[entryIndex].unit_price_float);
                        } else {
                            scanf("%i", &entries[entryIndex].unit_price_int);
                        }
                        break;
                    case 6:
                        printf("Enter quantity:\n");
                        printf("Tons: ");
                        scanf("%f", &entries[entryIndex].quantity.tons);
                        printf("Kilograms: ");
                        scanf("%f", &entries[entryIndex].quantity.kg);
                        printf("Grams: ");
                        scanf("%f", &entries[entryIndex].quantity.grams);
                        break;
                    default:
                        exit(0);
                }
                break;
            default:
                exit(0);
                break;
        }
    }
    
    return 0;
}

void swap_food_goods(Food_Goods* a, Food_Goods* b) {
    Food_Goods temp = *a;
    *a = *b;
    *b = temp;
}

int partition_by_commodity_name(Food_Goods* arr, int low, int high) {
    char *pivot = arr[high].commodity_name;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].commodity_name, pivot) < 0) {
            i++;
            swap_food_goods(&arr[i], &arr[j]);
        }
    }
    swap_food_goods(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_by_commodity_name(Food_Goods *arr, int low, int high) {
    if (low < high) {
        int pi = partition_by_commodity_name(arr, low, high);
        quick_sort_by_commodity_name(arr, low, pi - 1);
        quick_sort_by_commodity_name(arr, pi + 1, high);
    }
}

void print_food_goods(Food_Goods entry, int isFloat) {
    printf("Commodity name: %s\n", entry.commodity_name);
    printf("Manufacturer name: %s\n", entry.manufacturer);
    printf("Contract conclusion date: %i/%i/%i\n", entry.contract_conclusion_date.day, entry.contract_conclusion_date.month, entry.contract_conclusion_date.year);
    if(!isFloat) {
        printf("Wholesale price: %i$\n", entry.wholesale_price_int);
        printf("Unit price: %i$\n", entry.unit_price_int);
    } else {
        printf("Wholesale price: %.2f$\n", entry.wholesale_price_float);
        printf("Unit price: %.2f$\n", entry.unit_price_float);
    }
    printf("Quantity: %.2f tons, %.2f kg, %.2f grams\n", entry.quantity.tons, entry.quantity.kg, entry.quantity.grams);
}

void print_food_goods_arr(Food_Goods* arr, int n, int isFloat) {
    for(int i = 0; i < n; i++) {
        printf("\n----------------------------\n");
        print_food_goods(arr[i], isFloat);
    }
}

int partition_by_wholesale_price(Food_Goods* arr, int low, int high, int isFloat) {
    int pivot = arr[high].wholesale_price_int;
    if(isFloat) {
        pivot = arr[high].wholesale_price_float;
    }
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if(isFloat) {
            if (arr[j].wholesale_price_float < pivot) {
                i++;
                swap_food_goods(&arr[i], &arr[j]);
            }
        } else {
            if (arr[j].wholesale_price_int < pivot) {
                i++;
                swap_food_goods(&arr[i], &arr[j]);
            }
        }
    }
    swap_food_goods(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort_by_wholesale_price(Food_Goods *arr, int low, int high, int isFloat) {
    if (low < high) {
        int pi = partition_by_wholesale_price(arr, low, high, isFloat);
        quick_sort_by_wholesale_price(arr, low, pi - 1, isFloat);
        quick_sort_by_wholesale_price(arr, pi + 1, high, isFloat);
    }
}

int partition_by_unit_price(Food_Goods* arr, int low, int high, int isFloat) {
    int pivot = arr[high].unit_price_int;
    if(isFloat) {
        pivot = arr[high].unit_price_float;
    }
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if(isFloat) {
            if (arr[j].unit_price_float < pivot) {
                i++;
                swap_food_goods(&arr[i], &arr[j]);
            }
        } else {
            if (arr[j].unit_price_int < pivot) {
                i++;
                swap_food_goods(&arr[i], &arr[j]);
            }
        }
    }
    swap_food_goods(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort_by_unit_price(Food_Goods *arr, int low, int high, int isFloat) {
    if (low < high) {
        int pi = partition_by_unit_price(arr, low, high, isFloat);
        quick_sort_by_unit_price(arr, low, pi - 1, isFloat);
        quick_sort_by_unit_price(arr, pi + 1, high, isFloat);
    }
}

void counting_sort_by_commodity_name(Food_Goods* arr, int n) {
    int i, max = -1;
    for (i = 0; i < n; i++) {
        int len = strlen(arr[i].commodity_name);
        if (len > max)
            max = len;
    }
    int range = 256;
    Food_Goods* output = (Food_Goods*)malloc(n * sizeof(Food_Goods));
    int* count = (int*)malloc(range * sizeof(int));
    for (i = 0; i < range; ++i)
        count[i] = 0;
    for (i = 0; i < n; i++)
        ++count[arr[i].commodity_name[max - 1]];
    for (i = 1; i < range; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i].commodity_name[max - 1]] - 1] = arr[i];
        --count[arr[i].commodity_name[max - 1]];
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    free(output);
    free(count);
}

void counting_sort_by_wholesale_price(Food_Goods* arr, int n, int isFloat) {
    int max_price = 100000;
    Food_Goods* output = (Food_Goods*)malloc(n * sizeof(Food_Goods));
    int* count = (int*)calloc(max_price + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        if(isFloat) {
            count[(int)arr[i].wholesale_price_float]++;
        } else {
            count[arr[i].wholesale_price_int]++;
        }
    }
    for (int i = 1; i <= max_price; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        if(isFloat) {
            output[count[(int)arr[i].wholesale_price_float] - 1] = arr[i];
            count[(int)arr[i].wholesale_price_float]--;
        } else {
            output[count[arr[i].wholesale_price_int] - 1] = arr[i];
            count[arr[i].wholesale_price_int]--;
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
    free(count);
}

void counting_sort_by_unit_price(Food_Goods* arr, int n, int isFloat) {
    int max_price = 1000;
    Food_Goods* output = (Food_Goods*)malloc(n * sizeof(Food_Goods));
    int* count = (int*)calloc(max_price + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        if(isFloat) {
            count[(int)arr[i].unit_price_float]++;
        } else {
            count[arr[i].unit_price_int]++;
        }
    }
    for (int i = 1; i <= max_price; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        if(isFloat) {
            output[count[(int)arr[i].unit_price_float] - 1] = arr[i];
            count[(int)arr[i].unit_price_float]--;
        } else {
            output[count[arr[i].unit_price_int] - 1] = arr[i];
            count[arr[i].unit_price_int]--;
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
    free(count);
}