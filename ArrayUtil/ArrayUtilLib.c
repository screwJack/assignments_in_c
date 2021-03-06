#include "ArrayUtilLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ArrayUtil create(int typeSize, int length) {
	ArrayUtil array_util;
	array_util.base = calloc(length,sizeof(typeSize));
	array_util.typeSize = typeSize;
	array_util.length = length;
	return array_util;
};

int areEqual(ArrayUtil a, ArrayUtil b) {
	if(a.length == b.length && a.typeSize == b.typeSize) {
		char *ele1 = a.base;
		char *ele2 = b.base;
		for (int i = 0; i < a.length*a.typeSize; i++)
			if (ele1[i]!=ele2[i]) return 0;
		return 1;
	}	
	else return 0;
};

ArrayUtil resize(ArrayUtil util, int length) {
	util.base = realloc(util.base,length);
	util.length = length;
	return util;
};

int findIndex(ArrayUtil util, void* element) {
	char *ele = util.base;
	for (int i = 0; i < util.length; i++) 
		if(memcmp(ele + (i * util.typeSize), element ,util.typeSize) == 0)
			return i;
	return -1;
}

void my_print(ArrayUtil util) {
	int i = 0;
	char *ele = util.base;
	while(i < util.length*util.typeSize) {
		printf("%d\n", ele[i]);
		i++;
	};
};

void dispose(ArrayUtil util) {
	util.base = realloc(util.base,0);
	util.length = 0;
};

int isMatch(void* hint, void* item) {
	int first = *(int *)hint;
	int second = *(int *)item;
	if(first == second)
		return 1;
	return 0;
};

void* findFirst(ArrayUtil util, MatchFunc* match, void* hint) {
	void *element = util.base;
	for (int i = 0; i < util.length; ++i) {
		if(match(hint, element+(i*util.typeSize)))
			return element;	
	};
	return NULL;
};

void* findLast(ArrayUtil util, MatchFunc* match, void* hint) {
	void *element = util.base;
	for (int i = util.length; i > 0; --i) {
		if(match(hint, element+(i*util.typeSize)))
			return element;	
	};
	return NULL;
};

int count(ArrayUtil util, MatchFunc* match, void* hint) {
	void *element = util.base;
	int count = 0;
	for (int i = 0; i < util.length; ++i)	{
		if(match(hint, element+(i*util.typeSize)))
			count++;	
	};
	return count;
};

int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems) {
	char *pointer;
	int count = 0;
	void *element = util.base;
	void *filtered = destination;
	for (int i = 0; i < util.length; ++i) {
		if(match(hint, element+(i*util.typeSize)) && count <= maxItems) {
			memcpy((element+(i*util.typeSize)), (filtered + count), util.typeSize);	
			count++;
		};
	};
	return count;	
};

void square(void* hint, void* sourceItem, void* destinationItem) {
	int source = *(int *)sourceItem;
	int *destination = (int *)destinationItem;
	*destination = source*source;
};

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint) {
	for (int i = 0; i < source.length; ++i) {
		convert(hint, source.base, destination.base);
		source.base+=source.typeSize;
		destination.base+=destination.typeSize;
	};
};

void addNumber(void* hint, void* item) {
	int num = *(int *)hint;
	int *pointer = (int *)item;
	*pointer+=num;
};

void forEach(ArrayUtil util, OperationFunc* operation, void* hint) {
	for (int i = 0; i < util.length; ++i) {
		operation(hint, util.base);
		util.base+=util.typeSize;
	};
};

void reduceInSum (void* hint, void* previousItem, void* item) {
	int priv = *(int *)previousItem;
	int *current = (int *)item;
	*current+=priv;
};

void* reduce(ArrayUtil util, ReducerFunc* reducer, void* hint, void* intialValue) {
	for (int i = 0; i < util.length; ++i) {
		if(!i)
			reducer(hint, intialValue, util.base);
 	 	else
			reducer(hint, (util.base - util.typeSize), util.base);
		util.base+=util.typeSize;
	};
	int a = *(int *)util.base-4;
	printf("%p.............%d\n", util.base,a);
	return util.base;
};