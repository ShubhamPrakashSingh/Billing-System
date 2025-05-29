#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ITEMS 50

typedef struct {
    char itemName [50];
    int quantity;
    float price;
}

Item;

typedef struct {
    int invoiceId;
    char customerName[50];
    char date[20];
    Item items[MAX_ITEMS];
    int numItems;
    float total;
}
Invoice;

void createInvoice();
void viewAllInvoices();
void searchInvoice();
void saveInvoiceToFile(Invoice invoice);

int main() {
    int choice;
    while(1) {
        printf("\n ==== Billing System ====\n");
        printf("1. create Invoice\n");
        printf("2. viewAll Invoices\n");
        printf("3. search Invoice by ID \n");
        printf("4. Exit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        getchar(); // consume new line

       switch (choice)
       {
       case 1:
        createInvoice();
        break;
        case 2:
        viewAllInvoices();
        break;
        case 3:
        searchInvoice();
        break;
        case 4:
        printf("Exiting...\n");
        exit(0);
       
       default:
       printf("Invalid choice. Try again \n");
       }
    }
    return 0;
}

void createInvoice() { 
    Invoice invoice;
    invoice. total = 0;

    printf("\n Enter Invoice ID: ");
    scanf("%d", &invoice.invoiceId);
    getchar();

    printf("Enter Customer Name : ");
    fgets(invoice.customerName, sizeof(invoice.customerName), stdin);

    invoice.customerName[strcspn(invoice.customerName, "\n")] = 0;

    printf("Enter Date(DD-MM-YYYY): ");
    fgets(invoice.date, sizeof(invoice.date), stdin);

    invoice.date[strcspn(invoice.date,"\n")] = 0;

    printf("Enter number of items : ");
    scanf("%d", &invoice.numItems);

    for (int i = 0; i < invoice.numItems; i++)
    {
        printf("\n item #%d\n", i+1);
        printf("Name: ");
        getchar(); // clean input buffer

        fgets(invoice.items[i].itemName, sizeof(invoice.items[i].itemName), stdin);

        invoice.items[i].itemName[strcspn(invoice.items[i]. itemName, "\n")] = 0;


        printf("Quantity : ");
        scanf("%d", &invoice.items[i].quantity);

        printf("Price : ");
        scanf("%f", &invoice.items[i].price);

        invoice.total += invoice.items[i].quantity * invoice.items[i].price;
    }

    saveInvoiceToFile (invoice); 
    printf("\n Invoice saved successfully ! \n");
}

void saveInvoiceToFile(Invoice invoice) {
    FILE * fp = fopen ("invoices.dat", "ab");

    if (fp ==NULL) {
        printf("Error opening file !\n");
        return;
    }

    fwrite(&invoice,sizeof(Invoice), 1 ,fp);
    fclose(fp);
}

 void viewAllInvoices() {
    FILE*fp = fopen("invoices.dat", "rb");

    if(fp == NULL) {
        printf("No invoices found. \n");
        return;
    }

    Invoice invoice ;
    printf("\n == AllInvoices == \n");

    while (fread (&invoice, sizeof(Invoice),1 , fp)) {
        printf("\nInvoice ID: %d\n", invoice. invoiceId);
        printf("\ncustomer: %s\n", invoice. customerName);
        printf("Date: %s\n", invoice.date);
        printf("Items:\n");

        for (int i = 0; i < invoice.numItems; i++)
        {
            printf("%s x%d @%.2f = %.2f\n",
            invoice.items[i].itemName,
            invoice.items[i].quantity,
            invoice.items[i].price,
            invoice.items[i].quantity * invoice.items[i].price);
        }
        printf("Total:%.2f\n", invoice.total);
    }
    fclose(fp);
}

void searchInvoice() { 
    int id, found = 0;
    printf("Enter Invoice ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen("invoice.dat", "rb");

    if(fp == NULL) {
        printf("NO invoices found.\n");
        return;
    }

    Invoice invoice;
    while(fread(&invoice,sizeof(Invoice), 1, fp)) {
        if(invoice.invoiceId == id){
            found = 1;

            printf("\n Invoice ID: %d\n", invoice.invoiceId);
            printf("customer: %s\n", invoice.customerName);
            printf("Date: %s\n", invoice.date);
            printf("Items: \n");

            for (int i = 0; i < invoice.numItems; i++)
            {
                printf(" %s x%d @ %.2f = %.2f\n",
                
                    invoice.items[i].itemName,
                    invoice.items[i].quantity,
                    invoice.items[i].price,
                    invoice.items[i].quantity * invoice.items[i].price);
            }
            printf("Total: %.2f\n", invoice.total);
            break;
        }
    }
    if(!found)
    printf("Invoice with ID %d not found.\n", id);
    fclose(fp);
}