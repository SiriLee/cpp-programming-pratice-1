#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Snake {
    int x, y;
    int direction; // 0: right, 1: down, 2: left, 3: up
    void turnRight() {
        direction = (direction + 1) % 4;
    }
    void moveForward() {
        if (direction == 0) ++y;
        else if (direction == 1) ++x;
        else if (direction == 2) --y;
        else if (direction == 3) --x;
    }
    void moveBackward() {
        if (direction == 0) --y;
        else if (direction == 1) --x;
        else if (direction == 2) ++y;
        else if (direction == 3) ++x;
    }
};

void snakeMatrix(vector<vector<ll>>& matrix) {
    int N = matrix.size();
    Snake snake = {0, 0, 0};
    for (int i = 1; i <= N * N; ++i) {
        matrix[snake.x][snake.y] = i;
        snake.moveForward();
        if (snake.x < 0 || snake.x >= N || snake.y < 0 || snake.y >= N || matrix[snake.x][snake.y] != 0) {
            snake.moveBackward();
            snake.turnRight();
            snake.moveForward();
        }
    }
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        int N; cin >> N;
        cout << "case #" << i << ":" << endl;
        vector<vector<ll>> matrix(N, vector<ll>(N));
        snakeMatrix(matrix);
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                cout << matrix[j][k] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}