#include"bintree.h"
void main()
{
	BinTreeNode* Q;
	BinTreeInit(&Q);
	int index = 0;
	const BinTreeElemType* str = "ABC##DE##F##G#H##";
	Q = BinTreeCreate_2(str, &index);
	BinTreeVLR(Q);
	printf("\n");
	BinTreeLVR(Q);
	printf("\n");
	BinTreeLRV(Q);
	printf("\n");
	BinTreeLevel(Q);
	printf("\n");
}