#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "sht_table.h"
#include "ht_table.h"
#include "record.h"

#define CALL_OR_DIE(call) {     \
    BF_ErrorCode code = call;   \
    if (code != BF_OK) {        \
        BF_PrintError(code);    \
        exit(code);             \
    }                           \
}                               \

typedef struct {
    int block_id;
    char name[15];
} entry;

int SHT_CreateSecondaryIndex(char *sfileName,  int buckets, char* fileName) {
    int fd1;
    BF_Block *block;
    BF_Block_Init(&block);
    entry *temp = malloc(sizeof(*temp));    // χρησιμοποιoύμε μια προσωρινή δομή entry για να αποθηκεύσουμε
    temp->block_id = buckets;               // τον αριθμό κάδων κατακερματισμού και το όνομα αρχείου πρωτεύοντος ευρετηρίου
    if(strlen(fileName) + 1 > 15) {         // προσωρινά στο πρώτο block για να μπορέσουμε να ενημερώσουμε στην open την sht_info
        printf("fileName can't have more than 14 characters\n");
        BF_Block_Destroy(&block);
        free(temp);
        return -1;
    }
    strcpy(temp->name, fileName);

    CALL_OR_DIE(BF_CreateFile(sfileName))
    CALL_OR_DIE(BF_OpenFile(sfileName, &fd1));

    void *data;
    CALL_OR_DIE(BF_AllocateBlock(fd1, block));
    data = BF_Block_GetData(block);
    memset(data, 0, BF_BLOCK_SIZE);
    memcpy(data, temp, sizeof(*temp));
    BF_Block_SetDirty(block);
    CALL_OR_DIE(BF_UnpinBlock(block));

    BF_Block_Destroy(&block);
    CALL_OR_DIE(BF_CloseFile(fd1));

    free(temp);
    return 0;
}

SHT_info* SHT_OpenSecondaryIndex(char *indexName) {
    printf("here?\n");
    SHT_info *info = malloc(sizeof(*info));
    BF_Block_Init(&(info->block));

    CALL_OR_DIE(BF_OpenFile(indexName, &(info->fileDesc)));

    void *data;
    CALL_OR_DIE(BF_GetBlock(info->fileDesc, 0, info->block));
    data = BF_Block_GetData(info->block);
    entry *temp = malloc(sizeof(*temp));
    memcpy(temp, data, sizeof(*temp));
    info->numBuckets = temp->block_id;
    strcpy(info->ht_filename, temp->name);
    info->hash_table = malloc(sizeof(int) * info->numBuckets);
    for(int i = 0; i < info->numBuckets; i++)
        info->hash_table[i] = 0;
    info->block_capacity = (BF_BLOCK_SIZE - sizeof(SHT_block_info)) / sizeof(entry);
    memcpy(data, info, sizeof(*info));

    free(temp);
    return info;
}

int SHT_CloseSecondaryIndex(SHT_info* sht_info) {
    void* data;
    data = BF_Block_GetData(sht_info->block);
    memcpy(data, sht_info, sizeof(*sht_info));
    BF_Block_SetDirty(sht_info->block);
    CALL_OR_DIE(BF_UnpinBlock(sht_info->block));

    BF_Block_Destroy(&(sht_info->block));
    CALL_OR_DIE(BF_CloseFile(sht_info->fileDesc));

    free(sht_info->hash_table);
    free(sht_info);

    return 0;
}

int SHT_SecondaryInsertEntry(SHT_info* sht_info, Record record, int block_id) {
    return 0;
}

int SHT_SecondaryGetAllEntries(HT_info* ht_info, SHT_info* sht_info, char* name) {
    return 0;
}