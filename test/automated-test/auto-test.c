#include <stdlib.h>
#include <stdio.h>
#define NR 3
#define NC 10

int main() {
  int errors;
  int i, j;
  char cmd1[1000];
  char cmd2[1000];

  const int inputs[NR][NC] = {
    { 0, 1, 2, 3, 4, 5, 6, 8, 10, 11 },
    { 0, 1, 2, 3, 4, 5, 10, 100, 1000, 10000 },
    { 0, 1, 2, 3, 4, 5, 10, 100, 1000, 10000 }
  };

  const char files[NR][100] = {
    "test/automated-test/test-cvmp/test1.cvmp",
    "test/automated-test/test-cvmp/test2.cvmp",
    "test/automated-test/test-cvmp/test3.cvmp",
  };

  const char outputs[NR][NC][100] = {
    {
      "REG [30]:\t1",
      "REG [30]:\t1",
      "REG [30]:\t2",
      "REG [30]:\t6",
      "REG [30]:\t24",
      "REG [30]:\t120",
      "REG [30]:\t720",
      "REG [30]:\t40320",
      "REG [30]:\t3628800",
      "REG [30]:\t39916800"
    },
    {
      "REG [30]:\t0",
      "REG [30]:\t1",
      "REG [30]:\t3",
      "REG [30]:\t6",
      "REG [30]:\t10",
      "REG [30]:\t15",
      "REG [30]:\t55",
      "REG [30]:\t5050",
      "REG [30]:\t500500",
      "REG [30]:\t50005000"
    },
    {
      "REG [30]:\t0\nREG [30]:\t0\nREG [30]:\t0",
      "REG [30]:\t1\nREG [30]:\t1\nREG [30]:\t1",
      "REG [30]:\t3\nREG [30]:\t3\nREG [30]:\t3",
      "REG [30]:\t6\nREG [30]:\t6\nREG [30]:\t6",
      "REG [30]:\t10\nREG [30]:\t10\nREG [30]:\t10",
      "REG [30]:\t15\nREG [30]:\t15\nREG [30]:\t15",
      "REG [30]:\t55\nREG [30]:\t55\nREG [30]:\t55",
      "REG [30]:\t5050\nREG [30]:\t5050\nREG [30]:\t5050",
      "REG [30]:\t500500\nREG [30]:\t500500\nREG [30]:\t500500",
      "REG [30]:\t50005000\nREG [30]:\t50005000\nREG [30]:\t50005000"
    }
  };

  errors = 0;
  for (i = 0; i < NR; i++) {
    for (j = 0; j < NC; j++) {
      sprintf(cmd1, "sed -e 's/&&/%d/g' %s > temp.cvm", inputs[i][j], files[i]);
      system(cmd1);

      system("./vm.out run temp.cvm > output.txt 2>&1");

      sprintf(cmd2, "echo '%s' > output-corr.txt", outputs[i][j]);
      system(cmd2);
      if (system("diff -q output.txt output-corr.txt")) {
        errors++;
        printf("ERROR: \t[%d] [%d]\n", i, j);
      }
    }
  }

  system("rm -rf temp.cvm");
  system("rm -rf output.txt");
  system("rm -rf output-corr.txt");

  printf("DONE\n");

  return errors;
}
