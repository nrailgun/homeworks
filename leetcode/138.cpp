// 简单思想，O(n log(n)) 复杂度。

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        map<RandomListNode *, RandomListNode *> m;
        
        RandomListNode *n = head;
        while (n) {
            RandomListNode *nn = new RandomListNode(n->label);
            m[n] = nn;
            n = n->next;
        }
        
        n = head;
        while (n) {
            RandomListNode *nn = m[n];
            nn->next = m[n->next];
            nn->random = m[n->random];
            n = n->next;
        }
        return m[head];
    }
};

// 这是一个 O(n) 时间的实现，实现起来小心指针操作。Trick 在于灵活复用 next 指针存储新节点，可以类比，内存也是一个 table，指针就是索引。
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (!head) {
			return NULL;
		}
		
		Node *n1 = NULL, *n2 = NULL;
		for (n1 = head; n1 != NULL; n1 = n1->next->next) {
			n2 = new Node(n1->val);
			n2->next = n1->next;
			n1->next = n2;
		}

		for (n1 = head; n1 != NULL; n1 = n1->next->next) {
			n2 = n1->next;
			if (n1->random) { // !
				n2->random = n1->random->next;
			}
		}

		Node *newHead = head->next;
		for (n1 = head; n1 != NULL; n1 = n1->next) {
			n2 = n1->next;
			n1->next = n2->next;
			if (n2->next) { // !
				n2->next = n2->next->next;
			}
		}
		return newHead;
	}
};
