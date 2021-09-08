#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool match = false;
    for (int j = 0; j < candidate_count; j++)
    {
        //checks if the inputted name matches the list of candidates
        if (strcmp(candidates[j].name, name) == 0)
        {
            candidates[j].votes++;
            match = true;
            return match;
        }
    }
    return match;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = candidates[0].votes;
    //winner count
    int win_cnt = 0;

    //loop to find the max votes and the number of winners
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes > candidates[k + 1].votes && candidates[k].votes >= max_votes)
        {
            win_cnt++;
            max_votes = candidates[k].votes;
        }

    }

    //declaring winners array now since size of array was determined by the number of winners
    string winners[win_cnt];

    //loop to see which candidates have the number of max votes
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes == max_votes)
        {
            winners[k] = candidates[k].name;
            printf("%s\n", winners[k]);
        }
    }

    return;
}