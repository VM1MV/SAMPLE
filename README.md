# SAMPLE
## Framework
![image](./fig.png)

## Requirements

    pip install -r requirements.txt

## Usage

- Preprocess using the MHSA paper method:

 
    We preprocess the original dataset using the method described in the MHSA paper. 
    For more details, you can refer to the following repository.

- trajectory prediction:


    python Spatial-temporal Perception Module.py
- Allocate service chains for each user:


    python Service chains allocation.py
- Simulate edge servers based on the predicted location information:


    python Simulated BaseStation.py
- Integrate user requests data, edge servers data, and microservice resource consumption data to generate pre-deployment data:


    python Geolife Data merging.py
- Generate pre-deployment strategies:

   
    python main.py

## ACKNOWNLEDGES
The implementations of MHSA is based on the following GitHub Repository. Thank for the work.

- MHSA: https://github.com/mie-lab/location-prediction
