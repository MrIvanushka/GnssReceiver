#include "CommonReceiverLocationEstimator.h"
#include "Log.h"
#include "DenseMatrix.h"

using namespace gnssRecv::receiverLocationEstimator;
using gnssRecv::math::Vector3;
using gnssRecv::math::DenseMatrix;

CommonReceiverLocationEstimator::CommonReceiverLocationEstimator(
	std::shared_ptr<ISatelliteTable> storage) : _storage(storage)
{}

std::pair<Vector3, double> CommonReceiverLocationEstimator::calculateLocation(double currentTime)
{
	static const double lightspeed = 299792.458;
	static const double earthAngularSpeed = 0.7292115e-4;

	Vector3 recorderLocation(0, 0, 0);
	double recorderTime = 0;

	const auto& satellites = _storage->satelliteParams();
	if (satellites.size() < 4)
	{
		LOG_ERROR("Satellite count is not enough to solve navigation task!");
		return {};
	}
	std::vector<double> pseudoranges(satellites.size());
	std::vector<Vector3> satLocations(satellites.size());

	for (auto i = 0u; i < satellites.size(); ++i)
	{
		pseudoranges[i] = lightspeed * satellites[i]->pseudoDelay();
		satLocations[i] = satellites[i]->location();
	}
	Vector3 delta;
	
	double quality = 0.001;
	bool mustLeave = false;
	do
	{
		std::vector<double> currentSigma = pseudoranges;
		DenseMatrix<double> H(satellites.size(), 4);
		std::vector<double> D(satellites.size());
		if (delta.magnitude() < quality && !mustLeave)
		{
			for (auto& satLocation : satLocations)
			{
				auto prevloc = satLocation;
				satLocation.x += satLocation.y * earthAngularSpeed * (satLocation - recorderLocation).magnitude() / lightspeed;
				satLocation.y -= prevloc.x * earthAngularSpeed * (satLocation - recorderLocation).magnitude() / lightspeed;
			}
			mustLeave = true;
		}
		for (auto currentRow = 0u; currentRow < currentSigma.size(); currentRow++)
		{
			D[currentRow] = (recorderLocation - satLocations[currentRow]).magnitude();
			H(currentRow, 0) = (recorderLocation.x - satLocations[currentRow].x) / D[currentRow];
			H(currentRow, 1) = (recorderLocation.y - satLocations[currentRow].y) / D[currentRow];
			H(currentRow, 2) = (recorderLocation.z - satLocations[currentRow].z) / D[currentRow];
			H(currentRow, 3) = 1;
			currentSigma[currentRow] -= (D[currentRow] + recorderTime);
		}
		auto transposedH = H.transpose();
		auto theta = (transposedH * H).inverse() * transposedH * currentSigma;
		delta = Vector3(theta[0], theta[1], theta[2]);
		recorderLocation = recorderLocation + delta;
		recorderTime += theta[3];
	} while (!mustLeave || delta.magnitude() > quality);

	return std::make_pair(recorderLocation, recorderTime);
}