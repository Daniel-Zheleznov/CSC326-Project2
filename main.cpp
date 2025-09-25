#include <iostream>
#include "LinkedGit.h"

int main() {
    //srand(time(0)); // For random hash generation

    CommitHistory master;
    master.commit("Initial commit");
    master.commit("Add README");
    master.commit("Implement login system");

    CommitHistory featureBranch;
    featureBranch.commit("Start feature X");
    featureBranch.commit("Fix bug in feature X");

    std::cout << "\n== Master Branch ==" << std::endl;
    master.log();

    std::cout << "\n== Feature Branch ==" << std::endl;
    featureBranch.log();

    std::cout << "\n== Reset last commit on master ==" << std::endl;
    master.reset();
    master.log();

    std::cout << "\n== Merged History ==" << std::endl;
    CommitHistory merged = CommitHistory::merge(master, featureBranch);
    merged.reset();
    merged.log();

    std::cout << "\n== Master Branch Unchanged after merge ==" << std::endl;
    master.log();

    std::cout << "\n== Feature Branch Unchanged after merge ==" << std::endl;
    featureBranch.log();

    return 0;
}