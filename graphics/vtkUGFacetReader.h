/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkUGFacetReader.h
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
// .NAME vtkUGFacetReader - read EDS Unigraphics facet files
// .SECTION Description
// vtkUGFacetReader is a source object that reads Unigraphics facet files.
// Unigraphics is a solid modelling system; facet files are the polygonal
// plot files it uses to create 3D plots.

#ifndef __vtkUGFacetReader_h
#define __vtkUGFacetReader_h

#include <stdio.h>
#include "vtkPolyDataSource.h"
#include "vtkShortArray.h"

class VTK_EXPORT vtkUGFacetReader : public vtkPolyDataSource 
{
public:
  const char *GetClassName() {return "vtkUGFacetReader";};
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object to extract all parts, and with point merging
  // turned on.
  static vtkUGFacetReader *New() {return new vtkUGFacetReader;};

  // Description:
  // Overload standard modified time function. If locator is modified,
  // then this object is modified as well.
  unsigned long GetMTime();

  // Description:
  // Specify Unigraphics file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Special methods for interrogating the data file.
  int GetNumberOfParts();

  // Description:
  // Retrieve color index for the parts in the file.
  short GetPartColorIndex(int partId);

  // Description:
  // Specify the desired part to extract. The part number must range between
  // [0,NumberOfParts-1]. If the value is =(-1), then all parts will be 
  // extracted. If the value is <(-1), then no parts will be  extracted but 
  // the part colors will be updated.
  vtkSetMacro(PartNumber,int);
  vtkGetMacro(PartNumber,int);

  // Description:
  // Turn on/off merging of points/triangles.
  vtkSetMacro(Merging,int);
  vtkGetMacro(Merging,int);
  vtkBooleanMacro(Merging,int);
  
  // Description:
  // Specify a spatial locator for merging points. By
  // default an instance of vtkMergePoints is used.
  void SetLocator(vtkPointLocator *locator);
  vtkGetObjectMacro(Locator,vtkPointLocator);

  // Description:
  // Create default locator. Used to create one when none is specified.
  void CreateDefaultLocator();

  // Description:
  // For legacy compatibiltiy. Do not use.
  void SetLocator(vtkPointLocator& locator) {this->SetLocator(&locator);};

protected:
  vtkUGFacetReader();
  ~vtkUGFacetReader();
  vtkUGFacetReader(const vtkUGFacetReader&) {};
  void operator=(const vtkUGFacetReader&) {};

  void Execute();

  char *FileName;
  vtkShortArray *PartColors;
  int PartNumber;
  int Merging;
  vtkPointLocator *Locator;
};

#endif


