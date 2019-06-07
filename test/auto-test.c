#include <stdlib.h>
#include <stdio.h>
#define NR 3
#define NC 10

int main() {
  int error;
  int i, j;
  char cmd1[1000];
  char cmd2[1000];

  const int inputs[NR][NC] = {
    {0, 1, 2, 3, 4, 5, 10, 11, 40, 50},
    {0, 1, 2, 3, 4, 5, 10, 100, 1000, 10000},
    {0, 1, 2, 3, 4, 5, 10, 100, 1000, 10000}
  };

  const char files[NR][100] = {
    "test/test-cvmp/test1.cvmp",
    "test/test-cvmp/test2.cvmp",
    "test/test-cvmp/test3.cvmp",
  };

  const char outputs[NR][NC][100] = {
    {
      "1",
      "1",
      "2",
      "6",
      "24",
      "120",
      "3628800",
      "39916800",
      "ERROR [ 8 ]:	arithmetic overflow",
      "ERROR [ 8 ]:	arithmetic overflow"
    },
    {
      "0",
      "1",
      "3",
      "6",
      "10",
      "15",
      "55",
      "5050",
      "500500",
      "50005000"
    },
    {
      "0\n0\n0",
      "1\n1\n1",
      "3\n3\n3",
      "6\n6\n6",
      "10\n10\n10",
      "15\n15\n15",
      "55\n55\n55",
      "5050\n5050\n5050",
      "500500\n500500\n500500",
      "50005000\n50005000\n50005000"
    }
  };

  for (i = 0; i < NR; i++) {
    for (j = 0; j < NC; j++) {
      sprintf(cmd1, "sed -e 's/&&/%d/g' %s > temp.cvm", inputs[i][j], files[i]);
      system(cmd1);

      system("./vm.out run temp.cvm > output.txt 2>&1");

      sprintf(cmd2, "echo '%s' > output-corr.txt", outputs[i][j]);
      system(cmd2);
      if (system("diff -q output.txt output-corr.txt")) {
        printf("ERROR: \t[%d] [%d]\n", i, j);
      }
    }
  }

  system("rm -rf temp.cvm");
  system("rm -rf output.txt");
  system("rm -rf output-corr.txt");

  printf("DONE\n");

  return 0;
}
