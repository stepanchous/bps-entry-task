#ifndef BPS_MESSAGE_H
#define BPS_MESSAGE_H

#include <stdint.h>
#include <stdio.h>

#define TAG_LENGTH 2
#define LENGTH_LENGTH 2

struct FieldMessage {
  char tag[TAG_LENGTH + 1];
  uint32_t length;
  char* value;
};

struct DataMessage {
  struct FieldMessage* data;
  uint32_t size;
  uint32_t capacity_;
};

struct DataMessages {
  struct DataMessage* data;
  uint32_t size;
  uint32_t capacity_;
};

struct DataMessages ReadDataMessages(FILE* input);

void DeleteDataMessages(struct DataMessages* data_messages);

#endif  // !BPS_MESSAGE_H
