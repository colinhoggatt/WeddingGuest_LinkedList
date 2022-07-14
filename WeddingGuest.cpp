#include "WeddingGuest.h"



WeddingGuest::WeddingGuest(): m_size()
{
	/*head = nullptr;
	head->next = nullptr;
	head->prev = nullptr;*/
	head = new Node;
	head->next = head;
	head->prev = head;
}

WeddingGuest::WeddingGuest(const WeddingGuest& other)
{
	/*if (head == nullptr)
	{
		Node* newNode = new Node;
		head = newNode;
		newNode->next = nullptr;
		newNode->prev = nullptr;
	}*/

	m_size = other.m_size;
	Node* curr = other.head->next; //curr starts after dummy node of other list
	WeddingGuest(); //call constructor for an empty list
	Node* tempHead = head;

	while (curr != other.head) //while we have not reached the dummy node of other
	{
		Node* newNode = new Node;
		newNode->value = curr->value;
		tempHead->next = newNode;
		newNode->prev = tempHead;
		tempHead = tempHead->next;
		m_size++;
	}

	//circularly linked list leads beginning and end back to dummy node, head
	head->prev = tempHead;
	tempHead->next = head;

}

WeddingGuest:: ~WeddingGuest()
{
	Node* curr = head;
	for (int i = 0; i <= m_size; i++)
	{
		Node* temp = curr->next;
		delete curr; 
		curr = temp;
		m_size--;
	}
}

const WeddingGuest& WeddingGuest:: operator=(const WeddingGuest& other)
{
	if (&other != this) //if not same list
	{
		//create copy of other and swap with this list
		WeddingGuest tempCopy(other);
		tempCopy.swapWeddingGuests(*this);
	}
	return *this;
}

bool WeddingGuest::noGuests() const
{
	if (m_size == 0)
		return true;
	else
		return false;
}

//EDIT??
int WeddingGuest::guestCount() const
{
	/*int count = 0;
	Node* curr = head->next;
	while (curr != head)
	{
		count++;
		curr = curr->next;
	}
	return count;*/
	return m_size;
}

bool WeddingGuest::inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
	Node* curr = head->next;
	if (noGuests())
	{
		Node* newGuest = new Node;
		newGuest->firstName = firstName; newGuest->lastName = lastName; newGuest->value = value;
		// SET POINTERS
		newGuest->prev = curr; newGuest->next = curr->next;
		curr->next = newGuest; newGuest->next->prev = newGuest;
		m_size++;
		return true;
	}
	//check if this guest already exists in the list
	while (curr != head)
	{
		if (curr->lastName < lastName && (curr->next->lastName > lastName || curr->next == head)) // if lastName is between the two nodes or is greater than the last name on the list
		{
			//insert Node here
			Node* newGuest = new Node;
			newGuest->firstName = firstName; newGuest->lastName = lastName; newGuest->value = value;
			// SET POINTERS
			newGuest->prev = curr; newGuest->next = curr->next;
			curr->next = newGuest; newGuest->next->prev = newGuest;
			m_size++;
			return true;
		}
		if (curr->lastName > lastName && curr->prev == head) //first item in list
		{
			Node* newGuest = new Node;
			newGuest->firstName = firstName; newGuest->lastName = lastName; newGuest->value = value;
			// SET POINTERS
			newGuest->prev = curr->prev; newGuest->next = curr;
			curr->prev = newGuest; head->next = newGuest;
			m_size++;
			return true;
		}
		if (curr->lastName == lastName) //if has the same lastName
		{
			if (curr->firstName == firstName)//???
				return false;
			if (curr->firstName < firstName && (curr->next->firstName > firstName || curr->next == head)) // if firstName is between the two nodes
			{
				//insert Node here
				Node* newGuest = new Node;
				newGuest->firstName = firstName; newGuest->lastName = lastName; newGuest->value = value;
				// SET POINTERS
				newGuest->prev = curr; newGuest->next = curr->next;
				curr->next = newGuest; newGuest->next->prev = newGuest;
				m_size++;
				return true;
			}
		}
		curr = curr->next;
	}
	return false;
}

bool WeddingGuest::alterGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
	Node* curr = head->next;
	while (curr != head)
	{
		if (curr->firstName == firstName && curr->lastName == lastName)
		{
			curr->value = value;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool WeddingGuest::inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
	Node* curr = head->next;
	while (curr != head)
	{
		if (curr->firstName == firstName && curr->lastName == lastName)
		{
			curr->value = value;
			return true;
		}
		curr = curr->next;
	}
	//the name does not already exist in the list
	//call inviteGuest
	inviteGuest(firstName, lastName, value);

	return true;
}

bool WeddingGuest::crossGuestOff(const std::string& firstName, const std::string& lastName)
{
	Node* curr = head->next;
	while (curr != head)
	{
		if (curr->firstName == firstName && curr->lastName == lastName)
		{
			//code to remove node
			Node* temp = curr;
			//set previous and next node's pointers to each other
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr = curr->next; //increment curr before deleting temp node
			delete temp;
			m_size--;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool WeddingGuest::invitedToTheWedding(const std::string& firstName, const std::string& lastName) const
{
	Node* curr = head->next;
	while (curr != head)
	{
		if (curr->firstName == firstName && curr->lastName == lastName)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool WeddingGuest::matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const
{
	Node* curr = head->next;
	while (curr != head)
	{
		if (curr->firstName == firstName && curr->lastName == lastName)
		{
			value = curr->value;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType& value) const
{
	int count = 0;
	if (0 <= i < m_size)
	{
		Node* curr = head->next;
		while (curr != head)
		{
			if (count == i)
			{
				firstName = curr->firstName; 
				lastName = curr->lastName; 
				value = curr->value;
				return true;
			}
			curr = curr->next;
			count++;
		}
	}
	return false;
}

void WeddingGuest::swapWeddingGuests(WeddingGuest& other)
{
	//swap head pointers/dummy nodes
	Node* tempHead = other.head;
	other.head = head;
	head = tempHead;
	//swap sizes
	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;

}

bool joinGuests(const WeddingGuest& odOne, const WeddingGuest& odTwo, WeddingGuest& odJoined)
{
	//clear odJoined first
	if (odJoined.guestCount() != 0)
	{

	}
	//
	std::string firstName; std::string lastName; GuestType value;
	std::string firstName2; std::string lastName2; GuestType value2;
	std::string firstName3; std::string lastName3; GuestType value3;

	for (int i = 0; i < odOne.guestCount(); i++) //iterate through odOne
	{
		odOne.verifyGuestOnTheList(i, firstName, lastName, value);
		for (int j = 0; j < odTwo.guestCount(); j++)  //iterate through odTwo
		{
			odTwo.verifyGuestOnTheList(j, firstName2, lastName2, value2);
			if (firstName2 == firstName && lastName2 == lastName && value2 == value) //if guest exists in both lists, break
			{
				break;
			}
			if (firstName2 == firstName && lastName2 == lastName && value2 != value) //if values do not match, do not insert into odJoined
				continue;
			//ERROR BELOW
			odJoined.inviteGuest(firstName2, lastName2, value2); //add guest from second list to joined list if it doesn't match with guest from first list
		}
		//if (firstName2 == firstName && lastName2 == lastName && value2 != value) //if values do not match, do not insert into odJoined
		//	continue;
		for (int k = 0; k < odJoined.guestCount(); k++)
		{
			odJoined.verifyGuestOnTheList(k, firstName3, lastName3, value3);
			if (firstName != firstName3 || lastName != lastName3)
			{
				if (k == odJoined.guestCount())
				{
					odJoined.inviteGuest(firstName, lastName, value);
				}
				continue;
			}
			break;
		}
		
		
	}
	
}