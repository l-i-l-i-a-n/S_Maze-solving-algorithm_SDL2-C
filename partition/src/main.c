#include "testpartition.h"
#include "graphviz.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    (testCreer() && testRecupererClasse() && testFusion() && testListerClasse() && testListerPartition()) ? puts("tests ok") : puts("erreur tests");

    partition_t part;
    int n;

    n = 10;
    part = creer(n);
    fusion(part, part.foret[0], part.foret[2]);
    fusion(part, part.foret[0], part.foret[8]);
    fusion(part, part.foret[3], part.foret[7]);

    drawPartitionGraph(part, n, "exemplePartition");

    detruirePartition(part);

    return 0;
}
