#include "helper.h"

// this method returns vector of vectors of points
std::vector<std::vector<int>> createVectorFromFile(const std::string &filename, const int &dim)
{
    std::ifstream csv_data(filename, std::ios::in);
    std::string line;
    if (!csv_data.is_open())
    {
        std::cout << "Error: opening file fail" << std::endl;
        std::exit(1);
    }
    std::string elem;
    std::vector<std::vector<int>> points;

    // read data
    while (std::getline(csv_data, line))
    {
        // Read the entire line of string line into the string stream sin
        std::istringstream line_stream(line);
        std::vector<int> point;
        for (int i = 0; i < dim; i++)
        {
            unsigned i_elem;
            // Read the characters in the string stream sin into the elem string, separated by ", "
            getline(line_stream, elem, ',');
            // transfer string to int.
            i_elem = atoi(elem.c_str());
            // add into point.
            point.push_back(i_elem);
        }
        // add into points.
        points.push_back(point);
    }
    csv_data.close();
    return points;
}

// this method creats a KD-Tree and it inserts all the points from a vector
std::unique_ptr<KDTree> createKDTreeFromVectors(const std::vector<std::vector<int>> &points, const int &dim)
{
    auto tree = std::make_unique<KDTree>(dim);
    for (std::size_t i = 0; i < points.size(); i++)
    {
        tree->insert(points.at(i));
    }
    return tree;
}

// this method creats a KD-Tree and it inserts all the points from the file to the tree
std::unique_ptr<KDTree> createKDTreeFromFile(const std::string &file_name, const int &dim)
{
    std::vector<std::vector<int>> points = createVectorFromFile(file_name, dim);
    return createKDTreeFromVectors(points, dim);
}

// this method is deprecated
// this method creats a 2d KD-Tree and it inserts all the points from the file to the tree
std::unique_ptr<KDTree> create_2d_KDTree_From_File(std::string file_name)
{
    auto tree = std::make_unique<KDTree>(2);
    std::string line;
    std::ifstream my_file(file_name);
    int x, y;
    while (std::getline(my_file, line))
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream line_stream(line);

        line_stream >> x >> y;

        tree->insert({x,
                      y});
    }
    return tree;
}