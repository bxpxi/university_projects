#ifndef LAB2_TESTS_H
#define LAB2_TESTS_H

#include <assert.h>
#include "tests.h"
#include "domain.h"
#include "validator.h"
#include "repository.h"
#include "service.h"
#include "utils.h"

void runTests();
void testDomain();
void testValidator();
void testRepo();
void testService();
void testUtils();

#endif //LAB2_TESTS_H
