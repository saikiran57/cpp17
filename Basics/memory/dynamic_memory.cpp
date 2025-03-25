#include <map>
#include <unordered_map>
#include <vector>

class Allocator
{
public:
    // Constructor initializes the memory allocation tree with boundaries
    explicit Allocator(int n)
    {
        m_memoryTree[-1] = -1;  // Set start boundary
        m_memoryTree[n] = n;    // Set end boundary
    }

    // Allocates a block of memory of given size, associated with a mID, and returns
    // the start index of the allocated block. Returns -1 if allocation is not possible.
    int allocate(int size, int mID)
    {
        int start = -1;  // Starting index for allocation

        // Iterate over the memory blocks (end_points , start_points)
        for (auto& [endPoint, startPoint] : m_memoryTree)
        {
            if (start != -1)
            {
                // If there is a previous block, calculate the potential end of the new block
                int const potentialEnd = endPoint - 1;
                // Check if the block is large enough for the requested size
                if (potentialEnd - start + 1 >= size)
                {
                    // Set the end of the new block in the tree
                    m_memoryTree[start] = start + size - 1;
                    // Record the allocation start point associated with mID
                    m_allocations[mID].emplace_back(start);
                    // Return the starting index of allocated block
                    return start;
                }
            }
            // Update start to be the next possible index after current block
            start = startPoint + 1;
        }
        // If no suitable block found, return -1
        return -1;
    }

    // Frees all blocks of memory associated with a mID, returns total size of freed memory
    int free(int mID)
    {
        int totalFreedSize = 0;  // Counter for total freed memory size

        // Iterate over all start points of blocks associated with mID
        for (int const& start : m_allocations[mID])
        {
            int const end = m_memoryTree[start];  // Fetch the corresponding end point
            // Calculate size of the current block to increment the total freed size
            totalFreedSize += end - start + 1;
            // Remove the block from the memory allocation tree
            m_memoryTree.erase(start);
        }
        // Remove mID from the allocation record
        m_allocations.erase(mID);

        // Return the total size of all freed blocks
        return totalFreedSize;
    }

private:
    // Map to track start and end points of allocated memory blocks
    std::map<int, int> m_memoryTree;
    // Unordered map to track allocations by mID, containing the start indexes of blocks
    std::unordered_map<int, std::vector<int>> m_allocations;
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size, mID);
 * int param_2 = obj->free(mID);
 */

int main()
{
    int const n = 8;
    int const size = 2;
    int const mID = 1;
    auto* obj = new Allocator(n);
    int const param_1 = obj->allocate(size, mID);
    int const param_2 = obj->free(mID);
}