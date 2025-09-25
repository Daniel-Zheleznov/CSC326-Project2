#pragma once

#include <iostream>
#include <ctime>
#include <sstream>

struct Commit {
	std::string timestamp;
	std::string message;

	Commit* pNext;
};

class CommitHistory {
private:
	Commit* pHead;

public:
	CommitHistory() {
		pHead = nullptr;
	}

	// This function should append/commit to the CommitHistory
	//   Arg0: std::string message
	//     This represents a pointer to the string that should be in the Commit
	void commit(std::string message) {
		Commit* pCommit = new Commit;

		std::ostringstream oss;
		oss << time(NULL);
		pCommit->timestamp = oss.str();
		pCommit->message = message;
		pCommit->pNext = nullptr;

		if (pHead == nullptr) {
			pHead = pCommit;
		} else {
			Commit* pTemp = pHead;
			while (pTemp->pNext != nullptr) {
				pTemp = pTemp->pNext;
			}

			pTemp->pNext = pCommit;
		}
	}

	// This function displays all commits in CommitHistory from latest
	void log() {
		if (this->pHead != nullptr) {
			std::string output;
			std::string current;

			Commit* pTemp = this->pHead;
			while (pTemp != nullptr) {
				current += "\"" + pTemp->message + "\"" + "\n\t";
				current += "Unix timestamp: " + pTemp->timestamp + "\n\n";
		
				output = current + output;

				pTemp = pTemp->pNext;

				current = "";
			}
		
			std::cout << output;
		} else {
			std::cout << "No commits." << std::endl;
		}
	}

	// This function removes the last commit from the history.
	void reset() {
		if (this->pHead == nullptr) {
			return;
		}

		// head node
		if (this->pHead->pNext == nullptr) {
			delete this->pHead;
			this->pHead = nullptr;
			return;
		}

		// goto last
		Commit* prev = nullptr;
		Commit* curr = this->pHead;
		while (curr->pNext != nullptr) {
			prev = curr;
			curr = curr->pNext;
		}

		// curr is last, prev is node before last
		prev->pNext = nullptr;
		delete curr;

		std::cout << "Last commit removed (reset)" << std::endl;
	}

	static CommitHistory merge(const CommitHistory& history, const CommitHistory& history1) {
		CommitHistory merged;

		// goto last of the first CommitHistory
		Commit* pCurr = history.pHead;
		while (pCurr != nullptr) {
			merged.commit(pCurr->message);

			pCurr = pCurr->pNext;
		}

		// goto last of the second CommitHistory (pHistory1)
		pCurr = history1.pHead;
		while (pCurr != nullptr) {
			merged.commit(pCurr->message);

			pCurr = pCurr->pNext;
		}

		std::cout << "Branches merged." << std::endl;

		return merged;
	}

	~CommitHistory() {
		Commit* curr = this->pHead;
		while (curr != nullptr) {
			Commit* next = curr->pNext;
			delete curr;
			curr = next;
		}
		this->pHead = nullptr;
	}
};
