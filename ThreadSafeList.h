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
        List() { //TODO: add your implementation
        }

        /**
         * Destructor
         */
        ~List(){ //TODO: add your implementation
        }

        class Node {
         public:
          T data;
          Node *next;
          pthread_mutex_t lock;
          Node(T* data_t,Node* next_t=NULL):data(data_t),next(next_t){
              pthread_mutex_init(&(this->lock), NULL);
          }
          Node* GetNext(bool lock_t=true){
              if(lock_t && this->next!=NULL){
                  pthread_mutex_lock(&(this->next->lock));
              }
              return this->next;
          }
          Node* SetNext(Node* next_t){
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
			//TODO: add your implementation
        }

        /**
         * Remove the node that its data equals to @param value
         * @param value the data to lookup a node that has the same data to be removed
         * @return true if a matched node was found and removed and false otherwise
         */
        bool remove(const T& value) {
			//TODO: add your implementation
        }

        /**
         * Returns the current size of the list
         * @return the list size
         */
        unsigned int getSize() {
			//TODO: add your implementation
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


};

#endif //THREAD_SAFE_LIST_H_