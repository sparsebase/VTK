/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImageAnisotropicDiffusion2D.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Thanks:    Thanks to C. Charles Law who developed this class.

Copyright (c) 1993-2001 Ken Martin, Will Schroeder, Bill Lorensen 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither name of Ken Martin, Will Schroeder, or Bill Lorensen nor the names
   of any contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkImageAnisotropicDiffusion2D - edge preserving smoothing.
//
// .SECTION Description
// vtkImageAnisotropicDiffusion2D  diffuses a 2d image iteratively.
// The neighborhood of the diffusion is determined by the instance
// flags. If "Edges" is on the 4 edge connected voxels
// are included, and if "Corners" is on, the 4 corner connected voxels
// are included.  "DiffusionFactor" determines how far a pixel value
// moves toward its neighbors, and is insensitive to the number of 
// neighbors chosen.  The diffusion is anisotropic because it only occurs
// when a gradient measure is below "GradientThreshold".  Two gradient measures
// exist and are toggled by the "GradientMagnitudeThreshold" flag.
// When "GradientMagnitudeThreshold" is on, the magnitude of the gradient,
// computed by central differences, above "DiffusionThreshold"
// a voxel is not modified.  The alternative measure examines each
// neighbor independently.  The gradient between the voxel and the neighbor
// must be below the "DiffusionThreshold" for diffusion to occur with
// THAT neighbor.

// .SECTION See Also
// vtkImageAnisotropicDiffusion3D

#ifndef __vtkImageAnisotropicDiffusion2D_h
#define __vtkImageAnisotropicDiffusion2D_h


#include "vtkImageSpatialFilter.h"
class VTK_IMAGING_EXPORT vtkImageAnisotropicDiffusion2D : public vtkImageSpatialFilter
{
public:
  static vtkImageAnisotropicDiffusion2D *New();
  vtkTypeRevisionMacro(vtkImageAnisotropicDiffusion2D,vtkImageSpatialFilter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // This method sets the number of interations which also affects the
  // input neighborhood needed to compute one output pixel.  Each iterations
  // requires an extra pixel layer on the neighborhood.  This is only relavent
  // when you are trying to stream or are requesting a sub extent of the "wholeExtent".
  void SetNumberOfIterations(int num);

  // Description:
  // Get the number of iterations.
  vtkGetMacro(NumberOfIterations,int);

  // Description:
  // Set/Get the difference threshold that stops diffusion. 
  // when the difference between two pixel is greater than this threshold,
  // the pixels are not diffused.  This causes diffusion to avoid sharp edges.
  // If the GradientMagnitudeThreshold is set, then gradient magnitude is used 
  // for comparison instead of pixel differences.
  vtkSetMacro(DiffusionThreshold,float);
  vtkGetMacro(DiffusionThreshold,float);
  
  // Description:
  // The diffusion factor specifies  how much neighboring pixels effect each other.
  // No diffusion occurs with a factor of 0, and a diffusion factor of 1 causes
  // the pixel to become the average of all its neighbors.
  vtkSetMacro(DiffusionFactor,float);
  vtkGetMacro(DiffusionFactor,float);

  // Description:
  // Choose neighbors to diffuse (6 faces, 12 edges, 8 corners).
  vtkSetMacro(Faces,int);
  vtkGetMacro(Faces,int);
  vtkBooleanMacro(Faces,int);
  vtkSetMacro(Edges,int);
  vtkGetMacro(Edges,int);
  vtkBooleanMacro(Edges,int);
  vtkSetMacro(Corners,int);
  vtkGetMacro(Corners,int);
  vtkBooleanMacro(Corners,int);

  // Description:
  // Switch between gradient magnitude threshold and pixel gradient threshold.
  vtkSetMacro(GradientMagnitudeThreshold,int);
  vtkGetMacro(GradientMagnitudeThreshold,int);
  vtkBooleanMacro(GradientMagnitudeThreshold,int);
  
protected:
  vtkImageAnisotropicDiffusion2D();
  ~vtkImageAnisotropicDiffusion2D() {};

  int NumberOfIterations;
  float DiffusionThreshold;
  float DiffusionFactor;  
  // to determine which neighbors to diffuse
  int Faces;
  int Edges;
  int Corners;
  // What threshold to use
  int GradientMagnitudeThreshold;
  
  void ThreadedExecute(vtkImageData *inData, vtkImageData *outData, 
                       int extent[6], int id);
  void Iterate(vtkImageData *in, vtkImageData *out, 
               float ar0, float ar1, int *coreExtent, int count);
private:
  vtkImageAnisotropicDiffusion2D(const vtkImageAnisotropicDiffusion2D&);  // Not implemented.
  void operator=(const vtkImageAnisotropicDiffusion2D&);  // Not implemented.
};

#endif



