#include "stock_market.h"

Person* create_person(char *name, int id) {
    Person* new_person;
    int i;
    new_person=(Person*)malloc(sizeof(Person));
    if (new_person!=NULL)
    {
        for (i=0;i<MAX_NAME_LEN;i++)
        {
            new_person->name[i]=name[i];
        }
        new_person->id=id;
    }
    return new_person;
}

Company* create_company(char *name, char *abbr, int order) {
    Company* new_company;
    int i;
    new_company=(Company*)malloc(sizeof(Company));
    if (new_company!=NULL)
    {
        for (i=0;i<MAX_NAME_LEN;i++)
        {
            new_company->name[i]=name[i];
        }
        for (i=0;i<10;i++)
        {
            new_company->stock_abbreviation[i]=abbr[i];
        }
        new_company->market_order=order;
    }
    return new_company;
}

void add_company_to_market(StockMarket *market, Company *company) {
    int count;
    count=market->company_count;
    if (count<=MAX_COMPANIES)
    {
        market->entries[count].company=company;
        market->entries[count].buy_requests=NULL;
        market->entries[count].sell_requests=NULL;
        market->company_count++;
    }

}

RequestNode* create_request_node(Person *p, int amount, float price) {
    RequestNode* new_request;
    new_request=(RequestNode*)malloc(sizeof(RequestNode));
    if (new_request!=NULL)
    {
        new_request->data.person=p;
        new_request->data.amount=amount;
        new_request->data.price_per_share=price;
        new_request->next=NULL;
    }
    return new_request;
}

void insert_sorted(RequestNode **head, RequestNode *node, int ascending) {
    RequestNode *curr;
    RequestNode *prev;
    if (*head==NULL && node!=NULL)
    {
        node->next=NULL;
        *head=node;

    }

    else if (*head!=NULL && node!=NULL)
    {
        curr=*head;
        prev=NULL;
        if (ascending==0)
        {

            while (curr && node->data.price_per_share <= curr->data.price_per_share)
            {
                prev=curr;
                curr=curr->next;
            }
            node->next=curr;
            if (prev)
            {       
                prev->next=node;
            }
            else
            {
                *head=node;
            }

        }
        else if (ascending==1)
        {

            while (curr && node->data.price_per_share >= curr->data.price_per_share)
            {
                prev=curr;
                curr=curr->next;
            }
            node->next=curr;
            if (prev)
            {
                prev->next=node;
            }
            else
            {
                *head=node;
            }

        }
    }

}

void delete_request(RequestNode **head,RequestNode* node)
{
    RequestNode* curr=*head;
    RequestNode* prev;
    prev=NULL;
    if (node!=NULL && curr!=NULL)
    {
        if (curr==node)
        {
            *head=curr->next;
            free(curr);

        }
        else
        {
            while (curr!=NULL && curr!=node)
            {
                prev=curr;
                curr=curr->next;
            }
            prev->next=curr->next;
            free(curr);

        }

    }
}

void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price) {
    RequestNode *node;
    RequestNode *curr;
    RequestNode *next_node;
    RequestNode *temp;
    int count;
    int i,j,person_index;
    int person_founded;
    person_founded=0;
    count=market->company_count;
    for (j=0;j<people_count;j++)
    {

        if (strcmp(people[j]->name,buyer_name)==0)
        {
            person_founded=1;
            person_index=j;
        }
    }
    if (person_founded==1)
    {
        node=create_request_node(people[person_index],amount,price);
        for (i=0;i<count;i++)
        {
            if (strcmp(market->entries[i].company->stock_abbreviation,company_abbr)==0)
            {
                curr=market->entries[i].sell_requests;
                while (curr!=NULL)
                {
                    if (price>=curr->data.price_per_share && curr->data.amount<=amount)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n",curr->data.amount,company_abbr,curr->data.price_per_share,curr->data.person->name,buyer_name);
                        amount=amount-curr->data.amount;
                        curr->data.amount=0;
                    }
                    else if (price>=curr->data.price_per_share && curr->data.amount>amount)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n",amount,company_abbr,curr->data.price_per_share,curr->data.person->name,buyer_name);
                        curr->data.amount-=amount;
                        amount=0;
                        break;
                    }
                    curr=curr->next;
                }
                node->data.amount=amount;
                if (amount>0)
                {
                    insert_sorted(&(market->entries[i].buy_requests),node,0);
                }
                temp=market->entries[i].sell_requests;
                while (temp!=NULL)
                {
                    next_node=temp->next;
                    if (temp->data.amount==0)
                    {
                        delete_request(&(market->entries[i].sell_requests),temp);
                    }
                    temp=next_node;
                }
            }
        }
    }
}

void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price) {
    RequestNode *node;
    RequestNode *curr;
    RequestNode *next_node;
    RequestNode *temp;
    int count;
    int i,j,index_person;
    int person_founded;
    person_founded=0;
    count=market->company_count;

    for (j=0;j<people_count;j++)
    {
        if (strcmp(people[j]->name,seller_name)==0)
        {
            person_founded=1;
            index_person=j;
        }
    }
    if (person_founded==1)
    {
        node=create_request_node(people[index_person],amount,price);
        for (i=0;i<count;i++)
        {
            if (strcmp(market->entries[i].company->stock_abbreviation,company_abbr)==0)

            {
                curr=market->entries[i].buy_requests;
                while (curr!=NULL)
                {
                    if (price<=curr->data.price_per_share && curr->data.amount<=amount)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n",curr->data.amount,company_abbr,price,seller_name,curr->data.person->name);
                        amount=amount-curr->data.amount;
                        curr->data.amount=0;
                    }
                    else if (price<=curr->data.price_per_share && curr->data.amount>amount)
                    {
                        printf("Trade executed: %d shares of %s at %.2f between %s, %s\n",amount,company_abbr,price,seller_name,curr->data.person->name);
                        curr->data.amount-=amount;
                        amount=0;
                        break;
                    }
                    curr=curr->next;
                }
                node->data.amount=amount;
                if (amount>0)
                {
                    insert_sorted(&(market->entries[i].sell_requests),node,1);
                }
                temp=market->entries[i].buy_requests;
                while (temp!=NULL)
                {
                    next_node=temp->next;
                    if (temp->data.amount==0)
                    {
                        delete_request(&(market->entries[i].buy_requests),temp);
                    }
                    temp=next_node;
                }
            }
        }
    }
}

void print_market(StockMarket *market)
{
    int i,count;
    count=market->company_count;
    for (i=0;i<count;i++)
    {
        printf("Company: %s (%s)\n",market->entries[i].company->name,market->entries[i].company->stock_abbreviation);
        printf("\tBuy Requests:\n");
        while (market->entries[i].buy_requests!=NULL)
        {
            printf("\t\t%s wants %d @ %.2f\n",market->entries[i].buy_requests->data.person->name,market->entries[i].buy_requests->data.amount,market->entries[i].buy_requests->data.price_per_share);
            market->entries[i].buy_requests=market->entries[i].buy_requests->next;
        }
        printf("\tSell Requests:\n");
        while (market->entries[i].sell_requests!=NULL)
        {
            printf("\t\t%s sells %d @ %.2f\n",market->entries[i].sell_requests->data.person->name,market->entries[i].sell_requests->data.amount,market->entries[i].sell_requests->data.price_per_share);
            market->entries[i].sell_requests=market->entries[i].sell_requests->next;
        }

    }
}
int main(void) {
    int i;
    StockMarket market;
    Person *population[MAX_PEOPLE];
    Company *c1;
    int people_count;

    market.company_count = 0;
    people_count = 0;

    population[people_count++] = create_person("Alice", 1);
    population[people_count++] = create_person("Bob", 2);
    population[people_count++] = create_person("Charlie", 3);
    population[people_count++] = create_person("Diana", 4);
    population[people_count++] = create_person("Eve", 5);
    population[people_count++] = create_person("Frank", 6);
    population[people_count++] = create_person("Grace", 7);
    
    for (i = 0; i < people_count; i++) {
        printf("Person %d: %s\n", i + 1, population[i]->name);
    }

    c1 = create_company("Alpha Corp", "ALP", 1);
    
    if (c1 != NULL) {
        printf("Company created: %s with abbreviation %s and market order %d\n", c1->name, c1->stock_abbreviation, c1->market_order);
    }
    
    add_company_to_market(&market, c1);
    
    printf("Market created with %d companies\n", market.company_count);

    insert_sell_request(&market, population, people_count, "Bob", "ALP", 40, 49.0);
    insert_sell_request(&market, population, people_count, "Charlie", "ALP", 30, 49.5);
    insert_sell_request(&market, population, people_count, "Diana", "ALP", 20, 50.0);

    insert_buy_request(&market, population, people_count, "Alice", "ALP", 60, 50.0);
    insert_buy_request(&market, population, people_count, "Eve", "ALP", 25, 49.0);
    insert_buy_request(&market, population, people_count, "Frank", "ALP", 15, 48.0);

    insert_sell_request(&market, population, people_count, "Grace", "ALP", 10, 48.5);

    print_market(&market);
    return 0;
}
