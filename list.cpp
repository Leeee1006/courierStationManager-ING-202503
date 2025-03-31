#include "list.h"

List* list_init(size_t elementSize, const char* fileName, size_t fileNameSize)
{
	List* list = (List*)safeMalloc(sizeof(List), "list_init");
	list->tail = list->head = (ListNode*)safeMalloc(sizeof(ListNode), "list_init");
	list->head->next = NULL;
	list->elementCount = 0;
	list->elementSize = elementSize;
	list->fileName = (char*)safeMalloc(fileNameSize, "list_init");
	strcpy_s(list->fileName, fileNameSize, fileName);
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rb");
	if (fp == NULL)
	{
		return list;
	}
	size_t count = 0;
	fread(&count, sizeof(size_t), 1, fp);
	for (int i = 0; i < count; i++)
	{
		void* data = safeMalloc(elementSize, "list_init");
		fread(data, elementSize, 1, fp);
		list_basicAdd(list, data);
	}
	fclose(fp);
	return list;
}

void list_save(List* list)
{
	FILE* fp = safeFopen(list->fileName, "wb");
	fwrite(&list->elementCount, sizeof(size_t), 1, fp);
	for (ListNode* cur = list->head; cur != list->tail; cur = cur->next)
	{
		fwrite(cur->next->data, list->elementSize, 1, fp);
	}
	fclose(fp);
}

void list_basicAdd(List* list, void* data)
{
	ListNode* node = (ListNode*)safeMalloc(sizeof(ListNode), "list_basicAdd");
	node->data = data;
	node->next = NULL;
	list->tail = list->tail->next = node;
	list->elementCount++;
}

void list_add(List* list, void* data)
{
	void* newData = safeMalloc(list->elementSize, "list_add");
	memcpy_s(newData, list->elementSize, data, list->elementSize);
	list_basicAdd(list, newData);
}

void list_delete(List* list, bool match(const void* data))
{
	for (ListNode* cur = list->head; cur != list->tail; )
	{
		if (match(cur->next->data))
		{
			if (cur->next == list->tail)
			{
				list->tail = cur;
			}
			ListNode* temp = cur->next;
			cur->next = temp->next;
			if (temp->data != NULL)
			{
				free(temp->data);
			}
			free(temp);
			list->elementCount--;
		}
		else
		{
			cur = cur->next;
		}
	}
}

ListNode* list_mergeSort(ListNode* head, ListNode* tail, size_t elementCount, bool cmp(const void* d1, const void* d2))
{
	if (elementCount <= 1)
	{
		return tail;
	}
	ListNode* pivot = head;
	for (int i = 0; i < elementCount / 2; i++)
	{
		pivot = pivot->next;
	}
	pivot = list_mergeSort(head, pivot, elementCount / 2, cmp);
	tail = list_mergeSort(pivot, tail, elementCount - elementCount / 2, cmp);
	ListNode* p1 = head, * p2 = pivot;
	while (p1 != pivot && p2 != tail)
	{
		if (!cmp(p1->next->data, p2->next->data))
		{
			if (p2->next == tail)
			{
				tail = p2;
			}
			ListNode* temp = p2->next;
			p2->next = temp->next;
			temp->next = p1->next;
			p1->next = temp;
		}
		p1 = p1->next;
	}
	return tail;
}

void list_sort(List* list, bool cmp(const void* d1, const void* d2))
{
	list->tail = list_mergeSort(list->head, list->tail, list->elementCount, cmp);
}

void* list_find(List* list, bool match(const void* data))
{
	for (ListNode* cur = list->head; cur->next != NULL; cur = cur->next)
	{
		if (match(cur->next->data))
		{
			return cur->next->data;
		}
	}
	return NULL;
}

void list_clear(List* list)
{
	while (list->head->next != NULL)
	{
		ListNode* temp = list->head->next;
		list->head->next = temp->next;
		if (temp->data != NULL)
		{
			free(temp->data);
		}
		free(temp);
	}
	list->tail = list->head;
	list->elementCount = 0;
}

void list_free(List* list)
{
	list_clear(list);
	free(list->head);
	free(list->fileName);
	free(list);
	list = NULL;
}
