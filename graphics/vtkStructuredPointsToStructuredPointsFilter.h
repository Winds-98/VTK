/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkStructuredPointsToStructuredPointsFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 1993-1998 Ken Martin, Will Schroeder, Bill Lorensen.

This software is copyrighted by Ken Martin, Will Schroeder and Bill Lorensen.
The following terms apply to all files associated with the software unless
explicitly disclaimed in individual files. This copyright specifically does
not apply to the related textbook "The Visualization Toolkit" ISBN
013199837-4 published by Prentice Hall which is covered by its own copyright.

The authors hereby grant permission to use, copy, and distribute this
software and its documentation for any purpose, provided that existing
copyright notices are retained in all copies and that this notice is included
verbatim in any distributions. Additionally, the authors grant permission to
modify this software and its documentation for any purpose, provided that
such modifications are not distributed without the explicit consent of the
authors and that existing copyright notices are retained in all copies. Some
of the algorithms implemented by this software are patented, observe all
applicable patent law.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF,
EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN
"AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


=========================================================================*/
// .NAME vtkStructuredPointsToStructuredPointsFilter - abstract filter class
// .SECTION Description
// vtkStructuredPointsToStructuredPointsFilter is an abstract filter class 
// whose subclasses take on input structured points and generate
// structured points on output.

// .SECTION See Also
// vtkExtractVOI vtkImageDifference vtkSweptSurface
// vtkTransformStructuredPoints

#ifndef __vtkStructuredPointsToStructuredPointsFilter_h
#define __vtkStructuredPointsToStructuredPointsFilter_h

#include "vtkStructuredPointsSource.h"
#include "vtkImageToStructuredPoints.h"

class VTK_EXPORT vtkStructuredPointsToStructuredPointsFilter : public vtkStructuredPointsSource
{
public:
  static vtkStructuredPointsToStructuredPointsFilter *New() {
    return new vtkStructuredPointsToStructuredPointsFilter;};
  const char *GetClassName() {return "vtkStructuredPointsToStructuredPointsFilter";};

  // Description:
  // Set / get the input data or filter.
  void SetInput(vtkStructuredPoints *input);
  void SetInput(vtkImageData *cache)
    {vtkImageToStructuredPoints *tmp = cache->MakeImageToStructuredPoints();
    this->SetInput(tmp->GetOutput()); tmp->Delete();}
  vtkStructuredPoints *GetInput();

  // Since input[0] and output are of same type, we can create this
  // method that defaults to just copying information.
  void ExecuteInformation();

protected:
  vtkStructuredPointsToStructuredPointsFilter() {};
  ~vtkStructuredPointsToStructuredPointsFilter() {};
  vtkStructuredPointsToStructuredPointsFilter(const vtkStructuredPointsToStructuredPointsFilter&) {};
  void operator=(const vtkStructuredPointsToStructuredPointsFilter&) {};
  
  // Since we know Inputs[0] is the same type as Outputs[0] we can
  // use CopyUpdateExtent of the data object to propagate extents.
  // It the filter has more than one input, all bets are off.
  // It is then up to the subclass to implement this method.
  int ComputeInputUpdateExtents(vtkDataObject *output);
};

#endif


