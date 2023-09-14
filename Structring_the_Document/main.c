#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
struct document get_document(char* text) {
       int count_para = 0;
    int count_sen = 0;
    int count_word = 0;
    int countt1 = 0;
    char *text_temp = text;


    struct document doc_;
    struct paragraph *para_ptr;
    para_ptr = (struct paragraph *)calloc(5, sizeof(struct paragraph));
    doc_.data = para_ptr;
    for (int i = 0; i < 5; i++)
    {
        para_ptr[i].data = (struct sentence *)calloc(20, sizeof(struct sentence));
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            para_ptr[i].data[j].data = (struct word *)calloc(50, sizeof(struct word));
        }
        
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            for (int k = 0; k < 50; k++)
            {
                para_ptr[i].data[j].data[k].data = (char *)calloc(35, sizeof(char)); 
            }
            
        }
        
    }

text_temp = text;

    int count_1 = 0, count_2 = 0, count_3 = 0, count_4 = 0;

    while (*text_temp != 0)
    {
        if ( *text_temp == ' ')
        {
            text_temp++;
        }
        else if (*text_temp == '.')
        {
            text_temp++;
            if (*text_temp == '\n')
            {
                doc_.data[count_1].sentence_count = count_sen;
                count_1++;
                count_4 = 0;
                count_3 = 0;
                count_2 = 0;
                count_para++;
                count_sen = 0;
                text_temp++;
            }
        }
        
        doc_.data[count_1].data[count_2].data[count_3].data[count_4] = *text_temp;
        
        count_4++;
        text_temp++;
        if(*text_temp == ' ')
        {
            count_3++;
            count_4 = 0; 
            count_word++;
            
        }
        else if (*text_temp == '.')
        {
            count_word++;
            doc_.data[count_1].data[count_2].word_count = count_word;
            count_2++;
            count_4 = 0;
            count_3 = 0;
            count_sen++;
            count_word = 0;
            
        }
        else if(*text_temp == '\n')
        {
            
            doc_.data[count_1].sentence_count = count_sen;
            count_1++;
            count_4 = 0;
            count_3 = 0;
            count_2 = 0;
            count_para++;
            count_sen = 0;
            
        }
        else if (*text_temp == 0)
        {
            doc_.data[count_1].sentence_count = count_sen;
            count_para++;
        }
    }
    count_para++;
    doc_.paragraph_count = count_para;
 
    return doc_;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    
    
    return Doc.data[(n-1)].data[(m-1)].data[(k-1)];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 

    return Doc.data[(m-1)].data[(k-1)];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[(k-1)];

}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}