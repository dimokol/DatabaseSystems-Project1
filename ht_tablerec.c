#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "ht_table.h"
#include "record.h"

#define CALL_OR_DIE(call) {     \
    BF_ErrorCode code = call;   \
    if (code != BF_OK) {        \
        BF_PrintError(code);    \
        exit(code);             \
    }                           \
}                               \

int hash(int key, int table_size) {
    int value = rand();

    for (int i = 0; i < key; ++i)
        value = value + i * 37;

    value = value % table_size;

    return value;
}

int HT_CreateFile(char *fileName, int buckets) {
    int fd1;
    BF_Block *block;
    BF_Block_Init(&block);

    CALL_OR_DIE(BF_Init(LRU));
    CALL_OR_DIE(BF_CreateFile(fileName))
    CALL_OR_DIE(BF_OpenFile(fileName, &fd1));

    void* data;

    CALL_OR_DIE(BF_AllocateBlock(fd1, block));  // Δημιουργία καινούριου block
    data = BF_Block_GetData(block);             // Τα περιεχόμενα του block στην ενδιάμεση μνήμη
    Record* rec = data;                         // Ο δείκτης rec δείχνει στην αρχή της περιοχής μνήμης data
    rec[0] = randomRecord();
    rec[1] = randomRecord();
    BF_Block_SetDirty(block);
    CALL_OR_DIE(BF_UnpinBlock(block));

    CALL_OR_DIE(BF_CloseFile(fd1));               //Κλείσιμο αρχείου και αποδέσμευση μνήμης
    CALL_OR_DIE(BF_Close());

    return 0;
}

HT_info *HT_OpenFile(char *fileName) {
    int fd1;
    BF_Block *block;

    CALL_OR_DIE(BF_Init(LRU));
    CALL_OR_DIE(BF_OpenFile(fileName, &fd1));
    int blocks_num;
    CALL_OR_DIE(BF_GetBlockCounter(fd1, &blocks_num));

    void* data;
    printf("Contents of Block %d\n\t",0);
    CALL_OR_DIE(BF_GetBlock(fd1, 0, block));
    data = BF_Block_GetData(block);
    Record* rec= data;
    printRecord(rec[0]);
    printf("\t");
    printRecord(rec[1]);
    CALL_OR_DIE(BF_UnpinBlock(block));

    BF_Block_Destroy(&block);
    CALL_OR_DIE(BF_CloseFile(fd1));

    return NULL;
}

int HT_CloseFile(HT_info *ht_info) {
    // BF_Block *block;

    // void* data;
    // CALL_OR_DIE(BF_GetBlock(HT_info->fileDesc, 0, block));
    // data = BF_Block_GetData(block);
    // CALL_OR_DIE(BF_UnpinBlock(block));

    // BF_Block_Destroy(&block);
    // CAL_OR_DIE(BF_CloseFile(ht_info->fileDesc));

    // free(ht_info->hash_table);
    // free(ht_info);L

    return 0;
}

int HT_InsertEntry(HT_info *ht_info, Record record) {
    // BF_Block *block;
    // void* data;

    // int bucket = hash(record.id, ht_info->numBuckets);
    // if(ht_info->hash_table[bucket] == 0) {
    //     int blocks_num;
    //     CALL_OR_DIE(BF_GetBlockCounter(ht_info->fileDesc, &blocks_num));
    //     ht_info->hash_table[bucket] = blocks_num;

    //     CALL_OR_DIE(BF_AllocateBlock(ht_info->fileDesc, block));
    //     data = BF_Block_GetData(block);

    // }
    // else {
    //     CALL_OR_DIE(BF_GetBlock(ht_info->fileDesc, ht_info->hash_table[bucket], block));
    //     data = BF_Block_GetData(block);
    // }
    // data = BF_Block_GetData(block);
    // Record* rec = data;
    // rec[0] = record;
    // BF_Block_SetDirty(block);
    // CALL_OR_DIE(BF_UnpinBlock(block));

    return 0;
}

int HT_GetAllEntries(HT_info *ht_info, void *value) {
    return 0;
}
