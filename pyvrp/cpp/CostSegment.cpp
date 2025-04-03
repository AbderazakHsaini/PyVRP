#include "CostSegment.h"

namespace pyvrp
{
CostSegment::CostSegment(ProblemData const &data, size_t vehicleType)
    : data_(data), vehicleType_(vehicleType), cost_(0)
{
    auto const &vehType = data.vehicleType(vehicleType);
    assert(vehType.DeltaH.size() == vehType.Conso.size() &&
           "DeltaH and Conso must have the same size.");
}

CostSegment CostSegment::merge(CostSegment const &seg1, CostSegment const &seg2)
{
    assert(seg1.vehicleType_ == seg2.vehicleType_ &&
           "Cannot merge segments with different vehicle types.");

    CostSegment merged(seg1.data_, seg1.vehicleType_);
    merged.cost_ = seg1.cost_ + seg2.cost_;
    return merged;
}

void CostSegment::update(Distance distance, Load currentLoad)
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

Cost CostSegment::cost() const
{
    return cost_;
}
}  // namespace pyvrp