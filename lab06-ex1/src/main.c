#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *word;
	int freq;
	struct node *next;
} node_t;

node_t *loadData(char *, node_t *);
node_t * searchNode(node_t *, char *);
node_t * createNewNode(char *);
node_t * insertAtEnd(node_t *, node_t *);
node_t * insertAtHead(node_t *, node_t *);
node_t * insertOrdered(node_t *, node_t *);
void freeList(node_t *);
void printList(node_t *);
int main(int argc, char **argv) {
	node_t *head = NULL;

	if (argc != 2) {
		printf("missing parameters !\n");
		exit(EXIT_FAILURE);
	}

	/** Load File into list data structure */
	head = loadData(argv[1], head);

	printList(head);
	freeList(head);
	return 0;
}

/**
 * it loads file's data inside list data structure
 * @param fileName
 * @param head
 * @return
 */
node_t *loadData(char *fileName, node_t *head) {
	FILE *fp;
	node_t *tmp_node;
	char tmp_word[1000];
	/** open file */
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("error in opening file !\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s", tmp_word) != EOF) {

		/**convert it  upper case */
		strlwr(tmp_word);

		tmp_node = searchNode(head, tmp_word);

		if (tmp_node == NULL) {
			/** is not yet inside list  */
			tmp_node = createNewNode(tmp_word);
			head = insertOrdered(head, tmp_node);
			//	head=insertAtEnd(head,tmp_node);
			//head=insertAtHead(head,tmp_node);

		} else {
			/** already existed just update its frequency */
			tmp_node->freq++;
		}

	}

	fclose(fp);
	return head;
}

/**
 * given head of list it search for key which is a word
 *  returns pointer to that node if it finds  otherwise  return NULL
 * @param head
 * @param key
 * @return
 */
node_t * searchNode(node_t *head, char *key) {
	node_t *res_node = NULL;
	node_t *tmp = NULL;
	//  list is still empty
	if (head == NULL) {
		return NULL;
	} else if (strcmp(head->word, key) == 0) { // list has just one element
		return head;
	}
	// visiting every element of list to find node by the key
	for (tmp = head; (tmp != NULL && res_node == NULL); tmp = tmp->next) {
		if (strcmp(tmp->word, key) == 0) {
			res_node = tmp;
		}
	}

	return res_node;
}

/**
 * it create a new dynamic node
 * @param wordToBeInsert
 * @return
 */
node_t * createNewNode(char *wordToBeInsert) {
	node_t *res_node = NULL;

	// allocate a new node
	res_node = (node_t *) malloc(sizeof(node_t));
	if (res_node == NULL) {
		printf(" error in node allocation !! \n");
		exit(EXIT_FAILURE);
	} else {
		// initialize
		res_node->freq = 1;
		res_node->word = NULL;
		res_node->next = NULL;
		// allocate word of newnode
		res_node->word = (char *) malloc(
				(strlen(wordToBeInsert) + 1) * sizeof(char));
		if (res_node->word == NULL) {
			printf(" error in node allocation  of word inside node!! \n");
			exit(EXIT_FAILURE);
		}
		strcpy(res_node->word, wordToBeInsert);
	}
	return res_node;
}

/**
 * 2.Tail insertions
 * @param head
 * @param node
 * @return
 */
node_t * insertAtEnd(node_t *head, node_t *node) {
	node_t *tmp = NULL;
	tmp = head;
	if (head == NULL) {
		head = node;
		return head;
	}
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = node;
	return head;
}

/**
 * 1. Head insertions.
 * @param head
 * @param node
 * @return
 */
node_t * insertAtHead(node_t *head, node_t *node) {
	if (head == NULL) {
		head = node;
		return head;
	}

	node->next = head;
	head = node;
	return head;
}

/**
 *  Ordered insertion
 * @param head
 * @param node
 * @return
 */
node_t * insertOrdered(node_t *head, node_t *node) {
	node_t *current = NULL;
	if (head == NULL) {
		return node;
	}

	current = head;
	while (current->next != NULL
			&& (strcmp(current->next->word, node->word) < 0)) {
		current = current->next;
	}

	if (strcmp(current->word, node->word) > 0 && head == current) {
		// case : new node should be inserted in head because its key is  minimum one
		// so we should also date head
		node->next = head;
		head = node;
	} else {
		node->next = current->next;
		current->next = node;
	}

	return head;
}

/**
 * free dynamic list
 * @param head
 */
void freeList(node_t *head) {
	node_t *tmp;
	while (head->next != NULL) {
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
	free(head);
	return;
}

/**
 * it prints the given  list
 * @param head
 */
void printList(node_t *head) {
	node_t *tmp;
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		printf("%s %d\n", tmp->word, tmp->freq);
	}
	return;
}

