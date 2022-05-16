#include "MoveObject.h"

//-------------------------------------
//crating whats nedded to bfs algo and sendig the cat place result
sf::Vector2i MoveObject::getNextMove(const BoardVector &board,  sf::Vector2i &src) {

    bool vis[BOARD_SIDE][BOARD_SIDE];
    sf::Vector2i prev[BOARD_SIDE][BOARD_SIDE];
    sf::Vector2i e;

    setArray(vis);
    
    if (findShortPath(board, vis, src, prev))
        return reversePrev(prev, src);

    return getCatPos();
}

//-------------------------------------
void MoveObject::setArray(bool vis[][BOARD_SIDE]) {
    for (int i = 0; i < BOARD_SIDE; ++i)
        for (int j = 0; j < BOARD_SIDE; ++j)
            vis[i][j] = false;
}

//-------------------------------------
//bfs algorithem 
bool MoveObject::findShortPath(const BoardVector& board, bool vis[][BOARD_SIDE],  sf::Vector2i& i, Vector2i prev[BOARD_SIDE][BOARD_SIDE])
{
    std::queue<std::pair<int, int>> q;

    // seting the first cell as visited and push it into the queue
    q.push({ getCatPos().x, getCatPos().y });

    vis[getCatPos().x][getCatPos().y] = true;

    // until the queue is not empty
    while (!q.empty())
    {
        std::pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;

        q.pop();

        int adjx, adjy;
        // calc from the new cell
        for (int k = 0; k < directions; k++)
        {
            adjx = x + dirctionRow[k];
            x % 2 == 0 ? adjy = y + dirColEvenOdd[k] :
                adjy = y + dirColOdd[k];

            i = Vector2i(adjx, adjy);

            if (isValid(board, vis, sf::Vector2i(adjx, adjy)))
            {
                q.push({ adjx, adjy });
                vis[adjx][adjy] = true;
                prev[adjx][adjy] = Vector2i(x, y);
             
                if (adjx == 10 || adjx == 0 || adjy == 0 || adjy == 10)
                    return true;
            }
        }
    }
    return false;
}

//-------------------------------------
// geting the next cat position
sf::Vector2i MoveObject::reversePrev(Vector2i prev[BOARD_SIDE][BOARD_SIDE],
    const sf::Vector2i& e) {
    std::vector<Vector2i> path;
    for (auto at = e; at != getCatPos(); at = prev[at.x][at.y]) {
        path.push_back(at);
    }
    return path[path.size() - 1];
}


//-------------------------------------
// checking if the cell is free to be visited
bool MoveObject::isValid(const BoardVector &board, bool vis[][BOARD_SIDE],
                  const sf::Vector2i &i)
{
    if (i.x < 0 || i.y < 0
        || i.x > BOARD_SIDE - 1 || i.y > BOARD_SIDE - 1)
        return false;

    if (vis[i.x][i.y])
        return false;

    if (board[i.x][i.y].getFillColor() == Color::Black)
        return false;

    return true;
}
//-------------------------------------
// when the cat is blocked choseing a smart rand location to go to.
Vector2i MoveObject::randomMove(bool& lost)
{
    int num, x, y;

    num = rand() % directions;

    int count = 0;
    while (count < 6)
    {
        x = getCatPos().x + dirctionRow[num];

        getCatPos().x % 2 == 0 ? y = getCatPos().y + dirColEvenOdd[num] :
            y = getCatPos().y + dirColOdd[num];

        if (!isBlack(x, y))
            return { x, y };

        num = (num+1) % directions;
        count++;
    }

    lost = true;
    return getCatPos();
}