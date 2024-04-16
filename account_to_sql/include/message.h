#ifndef BPS_MESSAGE_H
#define BPS_MESSAGE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TAG_LENGTH 2
#define LENGTH_LENGTH 2

struct FieldMessage {
  char tag[TAG_LENGTH + 1];
  uint32_t length;
  char* value;
};

struct FieldMessage FieldMessageBuilder(char* tag, uint32_t length,
                                        char* value);

bool IsEqualFieldMessage(const struct FieldMessage* lhs,
                         const struct FieldMessage* rhs);

struct DataMessage {
  struct FieldMessage* data;
  uint32_t size;
  uint32_t capacity_;
};

struct DataMessage DataMessageBuilder(uint32_t count, ...);

void DeleteDataMessage(struct DataMessage* data_message);

bool IsEqualDataMessage(const struct DataMessage* lhs,
                        const struct DataMessage* rhs);

struct DataMessages {
  struct DataMessage* data;
  uint32_t size;
  uint32_t capacity_;
};

struct DataMessages NewDataMessages(void);
void MoveDataMessage(struct DataMessages* data_messages,
                     struct DataMessage* data_message);

struct DataMessages ReadDataMessages(FILE* input);

void DeleteDataMessages(struct DataMessages* data_messages);

bool IsEqualDataMessages(const struct DataMessages* lhs,
                         const struct DataMessages* rhs);

#endif  // !BPS_MESSAGE_H
