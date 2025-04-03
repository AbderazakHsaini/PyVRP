#ifndef PYVRP_COSTSEGMENT_H
#define PYVRP_COSTSEGMENT_H

#include "ProblemData.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace pyvrp
{
/**
 * CostSegment(data: ProblemData, vehicleType: size_t)
 *
 * A class that calculates and stores the cost of a segment based on the
 * weight intervals (DeltaH) and fuel consumption rates (Conso) of a vehicle type.
 */
class CostSegment
{
public:
    CostSegment(ProblemData const &data, size_t vehicleType)
        : data_(data), vehicleType_(vehicleType), cost_(0)
    {
        auto const &vehType = data.vehicleType(vehicleType);
        assert(vehType.DeltaH.size() == vehType.Conso.size() &&
               "DeltaH and Conso must have the same size.");
    }

    /**
     * Merges two cost segments into one, combining their costs.
     */
    static CostSegment merge(CostSegment const &seg1, CostSegment const &seg2)
    {
        assert(seg1.vehicleType_ == seg2.vehicleType_ &&
               "Cannot merge segments with different vehicle types.");

        CostSegment merged(seg1.data_, seg1.vehicleType_);
        merged.cost_ = seg1.cost_ + seg2.cost_;
        return merged;
    }

    /**
     * Updates the cost of the segment based on the distance and current load.
     */
    void update(Distance distance, Load currentLoad)
    {
        auto const &vehType = data_.vehicleType(vehicleType_);

        // Determine the weight interval and apply the corresponding fuel rate
        for (size_t h = 0; h < vehType.DeltaH.size(); ++h)
        {
            if (currentLoad >= vehType.DeltaH[h] &&
                (h == vehType.DeltaH.size() - 1 || currentLoad < vehType.DeltaH[h + 1]))
            {
                cost_ += vehType.Conso[h] * distance;
                break;
            }
        }
    }

    /**
     * Returns the total cost of the segment.
     */
    [[nodiscard]] Cost cost() const { return cost_; }

private:
    ProblemData const &data_;  // Reference to problem data
    size_t vehicleType_;       // Vehicle type associated with this segment
    Cost cost_;                // Total cost of the segment
};
}  // namespace pyvrp

#endif  // PYVRP_COSTSEGMENT_H