#include "../file_utils.c"
#include "../io_utils.c"
#include "../memory.c"

#define TEST_FILE             "test_file_utils.data"
#define TEST_CONTENT          "123"
#define TEST_CONTENT_LEN      3
#define TEST_FAIL_CONTENT     "1234"
#define TEST_FAIL_CONTENT_LEN 4

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main() {
  FileResult res;
  char buf[TEST_CONTENT_LEN + 1];

  // ==========================================================================
  // Write a test file
  // ==========================================================================

  res = File_Write(TEST_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0777, TEST_CONTENT, TEST_CONTENT_LEN);
  if (! res.ok) {
    printf("%d: %s: %s\n", __LINE__, TEST_FILE, strerror(errno));
    return 1;
  }
  assert(res.len == TEST_CONTENT_LEN);

  // ==========================================================================
  // Read a test file
  // ==========================================================================

  res = File_Read(buf, sizeof(buf), TEST_FILE);
  if (! res.ok) {
    printf("%d: %s: %s\n", __LINE__, TEST_FILE, strerror(errno));
    return 1;
  }
  assert(res.len == TEST_CONTENT_LEN);
  assert(! strcmp(buf, TEST_CONTENT));

  // ==========================================================================
  // Write a test file
  // ==========================================================================

  res = File_Write(TEST_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0777, TEST_FAIL_CONTENT, TEST_FAIL_CONTENT_LEN);
  if (! res.ok) {
    printf("%d: %s: %s\n", __LINE__, TEST_FILE, strerror(errno));
    return 1;
  }
  assert(res.len == TEST_FAIL_CONTENT_LEN);

  // ==========================================================================
  // Read a test file (expected error)
  // ==========================================================================

  res = File_Read(buf, sizeof(buf), TEST_FILE);
  assert(! res.ok);
  assert(errno == EFBIG);

  return 0;
}
