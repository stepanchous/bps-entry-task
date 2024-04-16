#include "message.h"

#include <ctype.h>
#include <stdlib.h>
#include "value_validation.h"

static struct DataMessage ReadDataMessage(FILE* input);
static int ReadFieldMessage(FILE* input, struct FieldMessage* field);

static int ReadTag(FILE* input, char* tag);
static int ReadLength(FILE* input, uint32_t* length);
static int ReadValue(FILE* input, uint32_t length, char* value);

static struct DataMessages NewDataMessages(void);
static void MoveDataMessage(struct DataMessages* data_messages,
                            const struct DataMessage* data_message);

static struct DataMessage NewDataMessage(void);
static struct DataMessage ReadDataMessage(FILE* input);
static void DeleteDataMessage(struct DataMessage* data_message);

static struct FieldMessage NewFieldMessage(void);
static void MoveFieldMessage(struct DataMessage* data_message,
                             const struct FieldMessage* field);
static void DeleteFieldMessage(struct FieldMessage* message);

static char PeakChar(FILE* input);

struct DataMessages ReadDataMessages(FILE* input) {
  int err = 0;
  struct DataMessages data_messages = NewDataMessages();

  while (!err && !feof(input)) {
    struct DataMessage data_message = ReadDataMessage(input);

    err = data_message.size == 0;

    if (!err) {
      MoveDataMessage(&data_messages, &data_message);
    }
  }

  if (err) {
    DeleteDataMessages(&data_messages);
  }

  return data_messages;
}

static struct DataMessage ReadDataMessage(FILE* input) {
  int err = 0;
  struct DataMessage data_message = NewDataMessage();

  char c;
  do {
    c = fgetc(input);
  } while (c != EOF && isspace(c));

  if (ungetc(c, input) == EOF) {
    err = 1;
  }

  while (!err && !feof(input) &&
         !(isspace(PeakChar(input)) || PeakChar(input) == EOF)) {
    struct FieldMessage field = NewFieldMessage();
    err = ReadFieldMessage(input, &field);

    if (!err) {
      MoveFieldMessage(&data_message, &field);
    }
  }

  if (!err) {
    while (isspace(PeakChar(input))) {
      fgetc(input);
    }
  }

  if (err) {
    DeleteDataMessage(&data_message);
  }

  return data_message;
}

static int ReadFieldMessage(FILE* input, struct FieldMessage* field) {
  int err = 0;

  err = ReadTag(input, field->tag);

  if (!err) {
    err = ReadLength(input, &field->length);
  }

  if (!err) {
    field->value = malloc((field->length + 1) * sizeof(char));
    ReadValue(input, field->length, field->value);
  }

  return err;
}

static int ReadTag(FILE* input, char* tag) {
  tag[TAG_LENGTH] = 0;

  return fread(tag, sizeof(char), TAG_LENGTH, input) != TAG_LENGTH &&
         IsAlphaNumeric(tag, TAG_LENGTH);
}

static int ReadLength(FILE* input, uint32_t* length) {
  int err = 0;

  char length_str[LENGTH_LENGTH + 1];
  length_str[LENGTH_LENGTH] = 0;

  err = fread(length_str, sizeof(char), LENGTH_LENGTH, input) != LENGTH_LENGTH;

  if (!err) {
    err = IsNumeric(length_str, LENGTH_LENGTH);
  }

  if (!err) {
    err = sscanf(length_str, "%u", length) != 1;
  }

  return err;
}

static int ReadValue(FILE* input, uint32_t length, char* value) {
  value[length] = 0;
  return fread(value, sizeof(char), length, input) != length;
}

static struct DataMessages NewDataMessages(void) {
  return (struct DataMessages){
      .data = NULL,
      .size = 0,
      .capacity_ = 0,
  };
}

static void MoveDataMessage(struct DataMessages* data_messages,
                            const struct DataMessage* data_message) {
  if (data_messages->size == data_messages->capacity_) {
    uint32_t new_capacity =
        data_messages->capacity_ == 0 ? 1 : 2 * data_messages->capacity_;

    data_messages->data = realloc(data_messages->data,
                                  new_capacity * sizeof(struct FieldMessage));
    data_messages->capacity_ = new_capacity;
  }

  data_messages->data[data_messages->size] = *data_message;

  ++data_messages->size;
}

void DeleteDataMessages(struct DataMessages* data_messages) {
  for (uint32_t i = 0; i < data_messages->size; ++i) {
    DeleteDataMessage(&data_messages->data[i]);
  }

  free(data_messages->data);

  data_messages->data = NULL;
  data_messages->size = 0;
  data_messages->capacity_ = 0;
}

struct FieldMessage NewFieldMessage(void) {
  return (struct FieldMessage){
      .value = NULL,
  };
}

static struct DataMessage NewDataMessage(void) {
  return (struct DataMessage){
      .data = NULL,
      .size = 0,
      .capacity_ = 0,
  };
}

static void MoveFieldMessage(struct DataMessage* data_message,
                             const struct FieldMessage* field) {
  if (data_message->size == data_message->capacity_) {
    uint32_t new_capacity =
        data_message->capacity_ == 0 ? 1 : 2 * data_message->capacity_;

    data_message->data =
        realloc(data_message->data, new_capacity * sizeof(struct FieldMessage));
    data_message->capacity_ = new_capacity;
  }

  data_message->data[data_message->size] = *field;

  ++data_message->size;
}

static void DeleteDataMessage(struct DataMessage* data_message) {
  for (uint32_t i = 0; i < data_message->size; ++i) {
    DeleteFieldMessage(&data_message->data[i]);
  }

  free(data_message->data);

  data_message->data = NULL;
  data_message->size = 0;
  data_message->capacity_ = 0;
}

static void DeleteFieldMessage(struct FieldMessage* message) {
  free(message->value);
}

static char PeakChar(FILE* input) {
  char c;

  c = fgetc(input);
  ungetc(c, input);

  return c;
}
