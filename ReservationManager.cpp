#include "ReservationManager.h"
#include <vector>
#include <iostream>

// ReservationManager.cpp
// All functions to be used for the linked list ReservationManager. Takes info and function with the Reservation class to get data within reservations.

// Constructor to initialize an empty ReservationManager list
ReservationManager::ReservationManager() {
	head = nullptr;
}

// Deconstructor to delete entire ReservationManager list if need be
ReservationManager::~ReservationManager() {
	Reservation* curr = head;
	while (curr != nullptr) {
		Reservation* next = curr->getNext();
		delete curr;
		curr = next;
	}
}

// ReservationManager.push_front() to add a reservation (node) to the front of the Reservation Manager list
void ReservationManager::push_front(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
		Reservation* newHead = new Reservation(ReservID, StudID, Name, ResourID, Date);
		newHead->setNext(head);
		head = newHead;
}

// ReservationManager.add() to add a reservation (node) at any point in the Reservation Manager
void ReservationManager::add(int pos, int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
	// Find reservation before position to add at
	Reservation* curr = head;
	for (int i = 0; i < pos - 1; i++) {
		if (curr == nullptr) {
			return;
		}
		curr = curr->getNext();
	}

	// If curr iterates to end of list then end
	if (curr == nullptr) {
		return;
	}

	// Add reservation at that position in the Reservation Manager list
	Reservation* newReserv = new Reservation(ReservID, StudID, Name, ResourID, Date);
	newReserv->setNext(curr->getNext());
	newReserv = curr->getNext();
}

// ReservationManager.remove() to remove a reservation (node) at any point in the Reservation Manager list
void ReservationManager::remove(int pos) {

	// Abort if Reservation Manager list is empty
	if (head == nullptr) {
		return;
	}

	// If the reservation you want to delete is at the front
	if (pos == 0) {
		Reservation* oldHead = head;
		head = head->getNext();
		delete oldHead;
		return;
	}

	// Iterate to reservation before the position you want to delete at
	Reservation* curr = head;
	for (int i = 0; i < pos - 1; i++) {
		if (curr == nullptr || curr->getNext() == nullptr) {
			return;
		}

		curr->setNext(curr->getNext());
	}

	// Make sure there's actually a reservation to delete before deleting it
	if (curr->getNext() == nullptr) {
		return;
	}
	Reservation* del = curr->getNext();
	curr->setNext(del->getNext());
	delete del;
}

// ReservationManager.print() to traverse list and print reservation info
void ReservationManager::print() const {
	Reservation* curr = head;
	while (curr != nullptr) {
		std::cout << "Reservation ID: " << curr->getReservationID()
			  << " | Student ID: " << curr->getStudentID()
			  << " | Student Name: " << curr->getStudentName()
			  << " | Resource ID: " << curr->getResourceID()
			  << " | Reservation Date: " << curr->getReservationDate() << std::endl;
		curr = curr->getNext();
	}
}

// ReservationManager.isEmpty() returns true if the list has no reservations
bool ReservationManager::isEmpty() const {
    return head == nullptr;
}

// ReservationManager.findById() traverses the list and returns the reservation
// with this ReservationID, or nullptr if there is none.  O(n)
const Reservation* ReservationManager::findById(int reservationId) const {
    for (const Reservation* curr = head; curr != nullptr; curr = curr->getNext()) {
        if (curr->getReservationID() == reservationId) {
            return curr;
        }
    }
    return nullptr;
}

// ReservationManager.findByResourceAndDate() returns the reservation holding this
// resource on this date, or nullptr if the resource is free that day.  O(n)
const Reservation* ReservationManager::findByResourceAndDate(const std::string& resourceId, const std::string& date) const {
    for (const Reservation* curr = head; curr != nullptr; curr = curr->getNext()) {
        if (curr->getResourceID() == resourceId && curr->getReservationDate() == date) {
            return curr;
        }
    }
    return nullptr;
}

// ReservationManager.removeById() removes the reservation with this ReservationID
// (unlike remove(pos), which removes by position). Returns false if not found.  O(n)
bool ReservationManager::removeById(int reservationId) {
    Reservation* prev = nullptr;
    Reservation* curr = head;

    while (curr != nullptr && curr->getReservationID() != reservationId) {
        prev = curr;
        curr = curr->getNext();
    }

    if (curr == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        head = curr->getNext();
    } else {
        prev->setNext(curr->getNext());
    }

    delete curr;
    return true;
}

// ReservationManager.getAllActive() returns a pointer to every reservation
// currently in the list, by walking it once. Used by the Search module so it
// can run its own linear search without needing access to 'head' directly.  O(n)
std::vector<const Reservation*> ReservationManager::getAllActive() const {
    std::vector<const Reservation*> all;
    for (const Reservation* curr = head; curr != nullptr; curr = curr->getNext()) {
        all.push_back(curr);
    }
    return all;
}

// ReservationManager.SortByReservID() to call the list to sort itself by Reservation ID
void ReservationManager::SortByReservID() {
        head = MergeSortReservID(head);
}

// ReservationManager.MergeSortReservID() acts as the main function that performs the merge sort by Reservation ID
Reservation* ReservationManager::MergeSortReservID(Reservation* first) {
        // Check if the linked list is empty or only has one node
        if (first == nullptr || first->getNext() == nullptr) {
                return first;
        }

        // Find midpoint of linked list
        Reservation* slow = first;
        Reservation* fast = first->getNext();

        while (fast != nullptr && fast->getNext() != nullptr) {
                slow = slow->getNext();
                fast = fast->getNext()->getNext();
        }

        // Split linked list into two halves by midpoint
        Reservation* second = slow->getNext();
        slow->setNext(nullptr);

        // Sort each half recursively
        Reservation* left = MergeSortReservID(first);
        Reservation* right = MergeSortReservID(second);

        // Call upon MergeReservID() to combine each half
        return MergeReservID(left, right);
}

// ReservationManager.MergeReservID() acts within the MergeSortReservID() function to merge both sorted halves together, also sorted
Reservation* ReservationManager::MergeReservID(Reservation* left, Reservation* right) {
        Reservation* mergedHead = nullptr;
        Reservation* tail = nullptr;

        while (left != nullptr && right != nullptr) {
                Reservation* chosen;

                if (left->getReservationID() <= right->getReservationID()) {
                        chosen = left;
                        left = left->getNext();
                }
                else {
                        chosen = right;
                        right = right->getNext();
                }

                if (mergedHead = nullptr) {
                        mergedHead = chosen;
                }
                else {
                        tail->setNext(chosen);
                }

                tail = chosen;
        }

        // Add which of the two lists still have nodes
        Reservation* remainder = (left != nullptr) ? left : right;
        if (mergedHead == nullptr) {
                return remainder;
        }

        remainder = tail->getNext();

        return mergedHead;
}

// ReservationManager.SortByResourID() to call the list to sort itself by Resource ID
void ReservationManager::SortByResourID() {
        head = MergeSortResourID(head);
}

// ReservationManager.MergeSortResourID() acts as the main function that performs the merge sort by Resource ID
Reservation* ReservationManager::MergeSortResourID(Reservation* first) {
        // Check if the linked list is empty or only has one node
        if (first == nullptr || first->getNext() == nullptr) {
                return first;
        }

        // Find midpoint of linked list
        Reservation* slow = first;
        Reservation* fast = first->getNext();
        while (fast != nullptr && fast->getNext() != nullptr) {
                slow = slow->getNext();
                fast = fast->getNext()->getNext();
        }
        // Split linked list into two halves by midpoint
        Reservation* second = slow->getNext();
        slow->setNext(nullptr);

        // Sort each half recursively
        Reservation* left = MergeSortResourID(first);
        Reservation* right = MergeSortResourID(second);

        // Call upon Merge() to merge each half
        return MergeResourID(left, right);
}

// ReservationManager.MergeResourID() acts within the MergeSortResourID() function to merge both sorted halves together, also sorted
Reservation* ReservationManager::MergeResourID(Reservation* left, Reservation* right) {
        Reservation* mergedHead = nullptr;
        Reservation* tail = nullptr;

        while (left != nullptr && right != nullptr) {
                Reservation* chosen;

                if (left->getResourceID() <= right->getResourceID()) {
                        chosen = left;
                        left = left->getNext();
                }
                else {
                        chosen = right;
                        right = right->getNext();
                }

                if (mergedHead = nullptr) {
                        mergedHead = chosen;
                }
                else {
                        tail->setNext(chosen);
                }

                tail = chosen;
        }

        // Add which of the two lists still have nodes
        Reservation* remainder = (left != nullptr) ? left : right;
        if (mergedHead == nullptr) {
                return remainder;
        }

        remainder = tail->getNext();

        return mergedHead;
}
