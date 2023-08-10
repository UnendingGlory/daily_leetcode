#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

struct Point {
    double x;
    double y;
};


// 计算两点之间的欧氏距离
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}


// 用所有数据点的坐标均值更新簇的中心
Point updateClusterCenter(const std::vector<Point>& points) {
    Point newCenter = {0.0, 0.0};
    for (const Point& p : points) {
        newCenter.x += p.x;
        newCenter.y += p.y;
    }
    newCenter.x /= points.size();
    newCenter.y /= points.size();
    return newCenter;
}


int main() {
    std::vector<Point> data = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {8.0, 8.0}, {9.0, 9.0}, {10.0, 10.0}};

    int k = 3; // 聚类数
    std::vector<Point> centers;
    for (int i = 0; i < k; ++i) {
        centers.push_back(data[i]);
    }

    std::vector<int> clusterAssignments(data.size(), -1); // 每个点的簇分配情况

    int maxIterations = 10;
    for (int iter = 0; iter < maxIterations; ++iter) {
        // 对每个点分配聚类中心
        for (size_t i = 0; i < data.size(); ++i) {
            double minDist = std::numeric_limits<double>::max();
            int assignedCluster = -1;
            for (size_t j = 0; j < centers.size(); ++j) {
                double dist = distance(data[i], centers[j]);
                if (dist < minDist) {
                    minDist = dist;
                    assignedCluster = j;
                }
            }
            clusterAssignments[i] = assignedCluster;
        }

        // 计算每个聚类（簇）中所有数据点的平均值，然后将这个平均值作为新的簇中心
        // 更新聚类簇的中心，调整簇的位置
        for (size_t i = 0; i < centers.size(); ++i) {
            std::vector<Point> pointsInCluster;
            for (size_t j = 0; j < data.size(); ++j) {
                if (clusterAssignments[j] == i) {
                    pointsInCluster.push_back(data[j]);
                }
            }
            if (!pointsInCluster.empty()) {
                centers[i] = updateClusterCenter(pointsInCluster);
            }
        }
    }

    // 输出结果
    for (size_t i = 0; i < centers.size(); ++i) {
        std::cout << "Cluster " << i + 1 << " center: (" << centers[i].x << ", " << centers[i].y << ")\n";
        for (size_t j = 0; j < data.size(); ++j) {
            if (clusterAssignments[j] == i) {
                std::cout << "Point (" << data[j].x << ", " << data[j].y << ") in cluster " << i + 1 << "\n";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
