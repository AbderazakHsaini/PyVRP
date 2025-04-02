#include "CostEvaluator.h"

using pyvrp::CostEvaluator;

CostEvaluator::CostEvaluator(std::vector<double> loadPenalties,
                             double twPenalty,
                             double distPenalty,
                             double fuelPenalty)  // Add fuel penalty
    : loadPenalties_(std::move(loadPenalties)),
      twPenalty_(twPenalty),
      distPenalty_(distPenalty),
      fuelPenalty_(fuelPenalty)  // Initialize fuel penalty
{
}

double CostEvaluator::evaluate(Cost distanceCost,
                                Cost durationCost,
                                Cost excessLoadCost,
                                Cost timeWarpCost,
                                Cost fuelConsumptionCost) const  // Add fuel cost
{
    return distPenalty_ * distanceCost +
           twPenalty_ * timeWarpCost +
           fuelPenalty_ * fuelConsumptionCost +  // Include fuel cost
           excessLoadCost + durationCost;
}
