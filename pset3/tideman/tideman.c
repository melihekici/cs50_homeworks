#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool cycle;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void go_all_nodes(int current, int base);



int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int j = 1; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j]) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        for (int j = k + 1; j < candidate_count; j++)
        {
            preferences[ranks[k]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Initializing the variables
    pair_count = 0;
    int p = -1;
    //Comparing each candidate with other candidates to see who is prefered more between them
    //Record findings to the pairs array together with loosers and winners
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if ((preferences[i][j] - preferences[j][i]) > 0)
            {
                p++;
                pairs[p].winner = i;
                pairs[p].loser = j;
                pair_count++;
            }
            else if ((preferences [j][i] - preferences[i][j]) > 0)
            {
                p++;
                pairs[p].winner = j;
                pairs[p].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair pairs_copy[pair_count];
    int preferences2 [MAX][MAX];

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            preferences2[i][j] = preferences[i][j];
        }
    }
    int max_p;

    for (int q = 0; q < pair_count; q++)
    {
        int max = 0;
        for (int p = 0; p < pair_count; p++)
        {
            if ((preferences2[pairs[p].winner][pairs[p].loser] - preferences2[pairs[p].loser][pairs[p].winner]) > max)
            {
                max = preferences2[pairs[p].winner][pairs[p].loser] - preferences2[pairs[p].loser][pairs[p].winner];
                max_p = p;
            }
        }
        pairs_copy[q] = pairs[max_p];
        preferences2[pairs[max_p].winner][pairs[max_p].loser] = 0;
    }
    for (int p = 0; p < pair_count; p++)
    {
        pairs[p] = pairs_copy[p];
    }
    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int p = 0; p < pair_count; p++)
    {
        cycle = false;
        locked[pairs[p].winner][pairs[p].loser] = true;
        go_all_nodes(pairs[p].loser, pairs[p].winner);
        if (cycle)
        {
            locked[pairs[p].winner][pairs[p].loser] = false;
        }
    }

}

// Print the winner of the election
void print_winner(void)
{
    int lost;
    for (int i = 0; i < candidate_count; i++)
    {
        lost = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                lost++;
            }
        }
        if (lost == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

//This is a recursive function and does the following:
//If the current node is the starting node stop and report a cycle and return
//If not, go to all possible nodes from current node
//Repeat
void go_all_nodes(int current, int base)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (current == base)
        {
            cycle = true;
            return;
        }
        else if (locked[current][i] == true)
        {
            go_all_nodes(i, base);
        }
    }
}



