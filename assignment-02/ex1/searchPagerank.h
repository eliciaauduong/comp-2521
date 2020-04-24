// write a simple search engine that given search terms (words) as commandline arguments, find pages with one or more search terms and outputs (to stdout) top 30 pages in descending order of number of search terms found and then within each group, descending order of weighted pagerank
// if number of matches are less than 30, output all of them 
/*
% ./searchPagerank  mars  design
    url31
    url25
    url2
    url101
*/

void findSearchPages(int numSearch, char **searchwords);

double findPagerank(char *page);

int countSearch(char *page);