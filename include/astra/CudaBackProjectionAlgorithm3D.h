/*
-----------------------------------------------------------------------
Copyright: 2010-2022, imec Vision Lab, University of Antwerp
           2014-2022, CWI, Amsterdam

Contact: astra@astra-toolbox.com
Website: http://www.astra-toolbox.com/

This file is part of the ASTRA Toolbox.


The ASTRA Toolbox is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASTRA Toolbox is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the ASTRA Toolbox. If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------
*/

#ifndef _INC_ASTRA_CUDABACKPROJECTIONALGORITHM3D
#define _INC_ASTRA_CUDABACKPROJECTIONALGORITHM3D

#include "Globals.h"
#include "Config.h"

#include "Algorithm.h"

#include "Data3D.h"
#include "ReconstructionAlgorithm3D.h"

#ifdef ASTRA_CUDA

namespace astra {

class _AstraExport CCudaBackProjectionAlgorithm3D : public CReconstructionAlgorithm3D {

protected:

	/** Check the values of this object.  If everything is ok, the object can be set to the initialized state.
	 * The following statements are then guaranteed to hold:
	 * - no NULL pointers
	 * - all sub-objects are initialized properly
	 * - the projector is compatible with both data objects
	 */
	virtual bool _check();

public:
	
	// type of the algorithm, needed to register with CAlgorithmFactory
	static inline const char* const type = "BP3D_CUDA";
	
	/** Default constructor, does not initialize the object.
	 */
	CCudaBackProjectionAlgorithm3D();

	/** Constructor with initialization.
	 *
	 * @param _pProjector		Projector Object.
	 * @param _pProjectionData	ProjectionData3D object containing the projection data.
	 * @param _pReconstruction	VolumeData3D object for storing the reconstructed volume.
	 */
	CCudaBackProjectionAlgorithm3D(CProjector3D* _pProjector, 
	                     CFloat32ProjectionData3D* _pProjectionData, 
	                     CFloat32VolumeData3D* _pReconstruction);
	
	/** Copy constructor.
	 */
	CCudaBackProjectionAlgorithm3D(const CCudaBackProjectionAlgorithm3D&);

	/** Destructor.
	 */
	virtual ~CCudaBackProjectionAlgorithm3D();

	/** Clear this class.
	 */
/*	virtual void clear();*/

	/** Initialize the algorithm with a config object.
	 *
	 * @param _cfg Configuration Object
	 * @return initialization successful?
	 */
	virtual bool initialize(const Config& _cfg);

	/** Initialize class.
	 *
	 * @param _pProjector		Projector Object.
	 * @param _pProjectionData	ProjectionData3D object containing the projection data.
	 * @param _pReconstruction	VolumeData3D object for storing the reconstructed volume.
	 * @return initialization successful?
	 */
	bool initialize(CProjector3D* _pProjector, 
					CFloat32ProjectionData3D* _pSinogram, 
					CFloat32VolumeData3D* _pReconstruction);

	/** Perform a number of iterations.
	 *
	 * @param _iNrIterations amount of iterations to perform.
	 */
	virtual bool run(int _iNrIterations = 0);

	/** Get a description of the class.
	 *
	 * @return description string
	 */
	virtual std::string description() const;

	/**  
	 * Sets the index of the used GPU index: first GPU has index 0
	 *
	 * @param _iGPUIndex New GPU index.
	 */
	void setGPUIndex(int _iGPUIndex) { m_iGPUIndex = _iGPUIndex; }

protected:

	int m_iGPUIndex;
	int m_iVoxelSuperSampling;

	/** Option to compute the column weights on the fly, divide by
	 *  them, and add the result to the current volume. This is both
	 *  more expensive and more GPU memory intensive than the regular
	 *  BP, but allows saving system RAM.
	 */
	bool m_bSIRTWeighting;


	void initializeFromProjector();
};

// inline functions
inline std::string CCudaBackProjectionAlgorithm3D::description() const { return CCudaBackProjectionAlgorithm3D::type; };

} // end namespace

#endif

#endif
