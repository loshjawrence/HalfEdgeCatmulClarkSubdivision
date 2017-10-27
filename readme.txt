(5 pts) When quadrangulating a face during Catmull-Clark subdivision, what information must you temporarily store in order to properly link your half-edge pointers without creating inaccessible edges?

The ring of halfedges that bound the orignal non-quadrangualted face.
As new quad faces are getting made you will take one of the halfedges that bound the orginal face and re-assign its next pointer to one of the 3 new halfedes that will be needed for the new quad face. By doing this you lose access to the remaining half edges... unless you store them temporarily before you begin the process.  

(5 pts) When extruding a face, what operation must be performed after all edges have been turned into quadrangles? What is an edge case in the scope of this operation?

You need to go around on all the new quad faces and setup sym pointers on halfedges between the new quad faces. The edge case would be if the 'face' was an just an edge and you were only creating one face (not back to back faces for the plane you are creating from the extruded edge). In this case, you have to create halfedge syms on the outside of the face that flow in the opposite direction (clockwise). These halfedges would point to null for their face.
