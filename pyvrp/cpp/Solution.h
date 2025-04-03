#ifndef PYVRP_SOLUTION_H
#define PYVRP_SOLUTION_H

#include "Measure.h"
#include "ProblemData.h"
#include "RandomNumberGenerator.h"
#include "Route.h"

#include <functional>
#include <iosfwd>
#include <optional>
#include <vector>

namespace pyvrp
{
/**
 * Solution(data: ProblemData, routes: list[Route] | list[list[int]])
 *
 * Encodes VRP solutions.
 */
class Solution
{
    using Client = size_t;
    using Depot = size_t;
    using VehicleType = size_t;

    using Routes = std::vector<Route>;
    using Neighbours = std::vector<std::optional<std::pair<Client, Client>>>;

    size_t numClients_ = 0;         // Number of clients in the solution
    size_t numMissingClients_ = 0; // Number of missing clients
    Distance distance_ = 0;        // Total distance of the solution
    Cost distanceCost_ = 0;        // Total distance cost
    Duration duration_ = 0;        // Total duration of the solution
    Cost durationCost_ = 0;        // Total duration cost
    Distance excessDistance_ = 0; // Excess distance
    std::vector<Load> excessLoad_; // Excess load
    Cost fixedVehicleCost_ = 0;    // Fixed vehicle cost
    Cost prizes_ = 0;              // Total prizes collected
    Cost uncollectedPrizes_ = 0;   // Total uncollected prizes
    Duration timeWarp_ = 0;        // Total time warp
    Cost fuelConsumption_ = 0;     // Total fuel consumption
    bool isGroupFeas_ = true;      // Group feasibility flag

    Routes routes_;                // List of routes in the solution
    Neighbours neighbours_;        // Neighbours for each client

    void makeNeighbours(ProblemData const &data);
    void evaluate(ProblemData const &data);

public:
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t numRoutes() const;
    [[nodiscard]] size_t numClients() const;
    [[nodiscard]] size_t numMissingClients() const;
    [[nodiscard]] Routes const &routes() const;
    [[nodiscard]] Neighbours const &neighbours() const;
    [[nodiscard]] bool isFeasible() const;
    [[nodiscard]] bool isGroupFeasible() const;
    [[nodiscard]] bool isComplete() const;
    [[nodiscard]] bool hasExcessLoad() const;
    [[nodiscard]] bool hasExcessDistance() const;
    [[nodiscard]] bool hasTimeWarp() const;
    [[nodiscard]] Distance distance() const;
    [[nodiscard]] Cost distanceCost() const;
    [[nodiscard]] Duration duration() const;
    [[nodiscard]] Cost durationCost() const;
    [[nodiscard]] std::vector<Load> const &excessLoad() const;
    [[nodiscard]] Distance excessDistance() const;
    [[nodiscard]] Cost fixedVehicleCost() const;
    [[nodiscard]] Cost prizes() const;
    [[nodiscard]] Cost uncollectedPrizes() const;
    [[nodiscard]] Duration timeWarp() const;

    /**
     * Returns the total fuel consumption for the solution.
     */
    [[nodiscard]] Cost fuelConsumption() const;

    bool operator==(Solution const &other) const;

    Solution(ProblemData const &data, RandomNumberGenerator &rng);
    Solution(ProblemData const &data,
             std::vector<std::vector<Client>> const &routes);
    Solution(ProblemData const &data, std::vector<Route> const &routes);
    Solution(size_t numClients,
             size_t numMissingClients,
             Distance distance,
             Cost distanceCost,
             Duration duration,
             Cost durationCost,
             Distance excessDistance,
             std::vector<Load> excessLoad,
             Cost fixedVehicleCost,
             Cost prizes,
             Cost uncollectedPrizes,
             Duration timeWarp,
             bool isGroupFeasible,
             Routes routes,
             Neighbours neighbours);
};

std::ostream &operator<<(std::ostream &out, Solution const &sol);
}  // namespace pyvrp

#endif  // PYVRP_SOLUTION_H
