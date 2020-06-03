#include "cars.h"

PorterCar::PorterCar()
    : BaseCar(2.750, 1.7, 1.6, "Porter")
{
}

bool PorterCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 1 && palletQuantity <= 2;
}

int PorterCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar* PorterCar::duplicate()
{
    return new PorterCar();
}

GazelCar::GazelCar()
    : BaseCar(3.7, 1.8, 1.6, "Gazel")
{
}

bool GazelCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 3 && palletQuantity <= 5;
}

int GazelCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 3) <= width)
        return 3;
    else if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar* GazelCar::duplicate()
{
    return new GazelCar();
}

MersedesCar::MersedesCar()
    : BaseCar(2.6, 1.4, 1.8, "Mersedes")
{
}

bool MersedesCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 1 && palletQuantity <= 2;
}

int MersedesCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar* MersedesCar::duplicate()
{
    return new MersedesCar();
}

FiveTonCar::FiveTonCar()
    : BaseCar(5.0, 2.4, 1.9, "FiveTonCar")
{
}

bool FiveTonCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 7 && palletQuantity <= 12;
}

int FiveTonCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 3) <= (width + 0.01))
        return 3;
    else if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar* FiveTonCar::duplicate()
{
    return new FiveTonCar();
}


TenTonCar::TenTonCar()
    : BaseCar(8.0, 2.4, 1.9, "TenTonCar")
{
}

bool TenTonCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 9 && palletQuantity <= 16;
}

int TenTonCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 3) <= (width + 0.01))
        return 3;
    else if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar* TenTonCar::duplicate()
{
    return new TenTonCar();
}


EuroTrackCar::EuroTrackCar()
    : BaseCar(13.6, 2.4, 2.6, "EuroTrack")
{
}

bool EuroTrackCar::isApplicaple(int palletQuantity)
{
    return palletQuantity >= 17 && palletQuantity <= 33;
}

int EuroTrackCar::getLoadWidth(double palletWidth)
{
    if ((palletWidth * 3) <= (width + 0.01))
        return 3;
    else if ((palletWidth * 2) <= width)
        return 2;
    else
        return 1;
}

BaseCar * EuroTrackCar::duplicate()
{
    return new EuroTrackCar();
}
