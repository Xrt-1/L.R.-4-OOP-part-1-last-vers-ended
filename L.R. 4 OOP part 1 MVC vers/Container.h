#pragma once
#include"Shape.h"
#include "MyForm.h"

namespace LR4OOPpart1lastvers {
	class shapes {
	private:
		class Node {
		public:
			Shape* value;
			Node* nextNode;
			Node(Shape& shape, Node* nxt = nullptr) {
				value = &shape;
				nextNode = nxt;
			}
			~Node() {
				delete value;
			}
		};
		Node* first;
		Node* current;
		Node* last;
		int size;
	public:
		shapes() {
			last = current = first = nullptr;
			size = 0;
		}
		Shape* getCurrent() {
			if (current->value != nullptr) return (current->value);
			else return nullptr;
		}
		Shape* getLast() {
			if (last != nullptr) return (last->value);
			else return nullptr;
		}
		int getSize() {
			return size;
		}
		void next() {
			if (current != nullptr) {
				current = current->nextNode;
			}
		}
		void resetCurrent() {
			current = first;
		}
		void push_back(Shape* cr) {
			Node* newNode = new Node(*cr);
			if (first == nullptr) {
				first = newNode;
			}
			else {
				last->nextNode = newNode;
				(last->value)->setIsSlctd(false);
			}
			last = newNode;
			size++;
		}
		
		void del(Shape* c) {
			if (c == nullptr || first == nullptr) return;
			Node* r = first;
			Node* p = nullptr; // Узел-предшественник удаляемого узла
			while (r != nullptr) {
				if (r->value == c) {
					if (p == nullptr) {
						// Если удаляемый узел - первый в списке
						if (current == first) current = first->nextNode;
						if (last == first) last = nullptr;
						Node* nxt = first->nextNode;
						delete first;
						first = nxt;
						size--;
						break;

					}
					else {
						// Удаляемый узел не первый в списке
						if (current == r) current = current->nextNode;
						if (last == r) {
							last = p;
							last->value->setIsSlctd(true);
						};
						p->nextNode = r->nextNode;
						delete r;
						size--;
						break;
					}
				}
				p = r;
				r = r->nextNode;
			}
		}
		void delSlctd() {
			Node* r = first;
			while (r != nullptr) {
				Node* nxt = r->nextNode;
				if (r->value->getIsSlctd()) del(r->value);
				r = nxt;
			}
		}
		void DrawAll(System::Drawing::Graphics^ g) {
			Node* r = first;
			while (r != nullptr) {
				(r->value)->Draw(g);
				r = r->nextNode;
			}
		}
		void unclick() {
			Node* r = first;
			while (r != nullptr) {
				if (r->value->getIsClckd()) {
					r->value->setIsClckd(false);
					r->value->setIsSlctd(false);
				}
				r = r->nextNode;
			}
		}
		void unslect() {
			unclick();
		}
	};
}


