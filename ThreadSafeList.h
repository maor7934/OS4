#ifndef THREAD_SAFE_LIST_H_
#define THREAD_SAFE_LIST_H_

#include <pthread.h>
#include <iostream>
#include <iomanip> // std::setw

using namespace std;

template <typename T>
class List 
{
    public:
        /**
         * Constructor
         */
        List(): size (0), head(NULL){
            pthread_mutex_init(&list_mutex, NULL);
            pthread_mutex_init(&mutex_2, NULL);
        }

        /**
         * Destructor
         */
        ~List() = default;

        class Node {
         public:
           T data;
          Node *next;
          pthread_mutex_t lock;
          Node( const T& data_t,Node* next_t=NULL):data(data_t),next(next_t){
              pthread_mutex_init(&(this->lock), NULL);
          }
          Node* GetNext(bool lock_t=true){
              if(lock_t && this->next!=NULL){
                  pthread_mutex_lock(&(this->next->lock));
              }
              return this->next;
          }
          void SetNext(Node* next_t){
              this->next = next_t;
          }
          void Unlock(){
              pthread_mutex_unlock(&(this->lock));
          }
          void Lock(){
                pthread_mutex_lock(&(this->lock));
          }
        };

        /**
         * Insert new node to list while keeping the list ordered in an ascending order
         * If there is already a node has the same data as @param data then return false (without adding it again)
         * @param data the new data to be added to the list
         * @return true if a new node was added and false otherwise
         */
        bool insert(const T& data) {

            pthread_mutex_lock(&list_mutex);

			if (this->head == NULL){
                Node* node = new Node(data);
                this->head = node;
                __add_hook();
                pthread_mutex_lock(&mutex_2);
                this->size++;
                pthread_mutex_unlock(&mutex_2);
                pthread_mutex_unlock(&list_mutex);
                return true;
			}
			this->head->Lock();
            if (data < this->head->data){
                Node* node = new Node(data);
                node->SetNext(head);
                this-> head = node;
                __add_hook();
                pthread_mutex_lock(&mutex_2);
                this->size++;
                pthread_mutex_unlock(&mutex_2);
                return true;
            }
            pthread_mutex_unlock(&list_mutex);
			Node* tmp_pointer = head;
            Node* tmp_pointer2= NULL    ;
			while (data > tmp_pointer->data){
			    if (tmp_pointer2 != NULL) {
                    tmp_pointer2->Unlock();
                }
			    tmp_pointer2 = tmp_pointer;
			    tmp_pointer = tmp_pointer->GetNext();
			    if (tmp_pointer == NULL){
                    Node* node = new Node(data);
			        tmp_pointer2->SetNext(node);
                    __add_hook();
                    pthread_mutex_lock(&mutex_2);
                    this->size++;
                    pthread_mutex_unlock(&mutex_2);
                    tmp_pointer2->Unlock();
			        return true;
			    }
			}
			if (data == tmp_pointer->data){
			    tmp_pointer->Unlock();
			    if (tmp_pointer2 != NULL){
                    tmp_pointer2->Unlock();
                }
			    return false;
			}
            Node* node = new Node(data);
			node->SetNext(tmp_pointer);
			tmp_pointer2->SetNext(node);
            __add_hook();
            pthread_mutex_lock(&mutex_2);
            this->size++;
            pthread_mutex_unlock(&mutex_2);
            tmp_pointer->Unlock();
            tmp_pointer2->Unlock();
            return true;
        }

        /**
         * Remove the node that its data equals to @param value
         * @param value the data to lookup a node that has the same data to be removed
         * @return true if a matched node was found and removed and false otherwise
         */
        bool remove(const T& value) {
            pthread_mutex_lock(&list_mutex);
            if (this->head == NULL) {
                pthread_mutex_unlock(&list_mutex);
                return false;
            }
            this->head->Lock();
            pthread_mutex_unlock(&list_mutex);
            Node* tmp_pointer = this->head;
            Node* tmp_pointer2;
            while (value > tmp_pointer->data){
                if (tmp_pointer2 != NULL) {
                    tmp_pointer2->Unlock();
                }
                tmp_pointer2 = tmp_pointer;
                tmp_pointer = tmp_pointer->GetNext();
                if (tmp_pointer == NULL){
                    tmp_pointer2->Unlock();
                    return false;
                }
            }
            if (tmp_pointer->data != value){
                tmp_pointer->Unlock();
                tmp_pointer2->Unlock();
                return false;
            }
            tmp_pointer2->SetNext(tmp_pointer->GetNext(false));
            delete(tmp_pointer);
            __remove_hook();
            tmp_pointer2->Unlock();
            pthread_mutex_lock(&mutex_2);
            this->size--;
            pthread_mutex_unlock(&mutex_2);
            return true;
        }

        /**
         * Returns the current size of the list
         * @return the list size
         */
        unsigned int getSize() {
            pthread_mutex_lock(&mutex_2);
           int return_arg = this->size;
            pthread_mutex_unlock(&mutex_2);
            return return_arg;
        }

		// Don't remove
        void print() {
          pthread_mutex_lock(&list_mutex);
          Node* temp = head;
          if (temp == NULL)
          {
            cout << "";
          }
          else if (temp->next == NULL)
          {
            cout << temp->data;
          }
          else
          {
            while (temp != NULL)
            {
              cout << right << setw(3) << temp->data;
              temp = temp->next;
              cout << " ";
            }
          }
          cout << endl;
          pthread_mutex_unlock(&list_mutex);
        }

		// Don't remove
        virtual void __add_hook() {}
		// Don't remove
        virtual void __remove_hook() {}
private:
    int size;
    Node* head;

    pthread_mutex_t list_mutex;
    pthread_mutex_t mutex_2;
    // TODO: Add your own methods and data members
};

#endif //THREAD_SAFE_LIST_H_