@section(Controls Controls for the Draw Demo)
@parent(DrawDemo)
@keyword(drawdemo)
@keyword(vdraw)
@keyword(vdrawres)
@keyword(controls)
@font(Times 14)
@bold(Controls for the Draw Demo)


The following controls of the draw demo program let you see some of
the features of the Galaxy Drawing Manager.


@popup(DrawDemoDedicated Fastest Checkbox)

@popup(DrawDemoDrawOnce Once Checkbox)

@popup(DrawDemoMonochrome Monochrome Checkbox)

@popup(DrawDemoXorColors X-or Colors Checkbox)

@popup(DrawDemoDashed Dashed Checkbox)

@popup(DrawDemoObjectType Object Type Menu)

@popup(DrawDemoFillType Fill Type Menu)

@popup(DrawDemoLineCap Line Caps Menu)

@popup(DrawDemoLineJoin Line Joints Menu)

@popup(DrawDemoObjectCount Number of Objects Item)

@popup(DrawDemoRotateAngle Rotation Angle Item)

@popup(DrawDemoScaleX Scale X Item)

@popup(DrawDemoScaleY Scale Y Item)

@popup(DrawDemoFlatness Flatness Item)

@popup(DrawDemoLineWidth Line Width Item)

@popup(DrawDemoMiterLimit Miter Limit Item)

@popup(DrawDemoStartBtn Start Button)

@popup(DrawDemoFontBtn Font Button)

@popup(DrawDemoCloseBtn Close Button)


@end(font)

@section(DrawDemoDedicated Fastest Checkbox)
@parent(DrawDemo)
@keyword(controls)
@keyword(fastest)
@font(Times 14)
@bold(Fastest Checkbox)


This changes how the draw demo does its drawing. When turned on, in
each pass through the drawing cycle, it will draw all of the objects;
when off, it will only draw one object on each pass. This makes a
difference in when clicks are checked to interrupt it.

@end(font)

@section(DrawDemoDrawOnce Once Checkbox)
@parent(DrawDemo)
@keyword(controls)
@keyword(once)
@font(Times 14)
@bold(Once Checkbox)


This causes the draw demo to automatically stop once it has drawn the
specified number of objects; otherwise, it clears the draw area and
starts again.

@end(font)

@section(DrawDemoMonochrome Monochrome Checkbox)
@parent(DrawDemo)
@keyword(controls)
@keyword(monochrome)
@font(Times 14)
@bold(Monochrome Checkbox)


This causes the demo to draw in only black and white instead of
picking random colors. (Color is dithered on 1-bit displays.)

@end(font)

@section(DrawDemoXorColors X-or Colors Checkbox)
@parent(DrawDemo)
@keyword(controls)
@keyword(x-or)
@font(Times 14)
@bold(X-or Colors Checkbox)


This causes the demo to X-or the colors into the drawing area instead
of just drawing the object in its current color.

@end(font)

@section(DrawDemoDashed Dashed Checkbox)
@parent(DrawDemo)
@keyword(controls)
@keyword(dashed)
@font(Times 14)
@bold(Dashed Checkbox)


This causes any lines drawn in the drawing area to be done in the
predefined dash patterns.

@end(font)

@section(DrawDemoObjectType Object Type Menu)
@parent(DrawDemo)
@keyword(controls)
@keyword(object type menu)
@font(Times 14)
@bold(Object Type Menu)


This allows you to select the type of object that the draw demo draws
into the draw area.

@end(font)

@section(DrawDemoFillType Fill Type Menu)
@parent(DrawDemo)
@keyword(controls)
@keyword(fill type menu)
@font(Times 14)
@bold(Fill Type Menu)


This controls how the objects are drawn, whether they are filled
and/or bordered. (See the sections in the Galaxy Documentation on fill
and clip methods.)

@end(font)

@section(DrawDemoLineCap Line Caps Menu)
@parent(DrawDemo)
@keyword(controls)
@keyword(line caps menu)
@font(Times 14)
@bold(Line Caps Menu)


This controls how the line ends are drawn. This affects the ends of
single line segments (see vdrawSetLineCap in the Galaxy
documentation).

@end(font)

@section(DrawDemoLineJoin Line Joints Menu)
@parent(DrawDemo)
@keyword(controls)
@keyword(line joints menu)
@font(Times 14)
@bold(Line Joints Menu)


This controls how the ends of the lines meet. So see what these
seeings do, set the line width to 20, and then let the demo draw lines
in outline only (see vdrawSetLineJoint in the Galaxy documentation).

@end(font)

@section(DrawDemoObjectCount Number of Objects Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(object count)
@font(Times 14)
@bold(Number of Objects Item)


This specifies how many objects to draw on each pass before clearing
the draw area.

@end(font)

@section(DrawDemoRotateAngle Rotation Angle Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(rotation angle)
@font(Times 14)
@bold(Rotation Angle Item)


The number of degrees to rotate the drawing area. The rotation is from
the bottom left corner of the draw area. Anything more than 90 will
rotate out of the draw area, until things are rotated enought to move
them back into view ( >270 ).

@end(font)

@section(DrawDemoScaleX Scale X Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(scale x)
@font(Times 14)
@bold(Scale X Item)


This the the horizontal scale to zoom in on the drawing. Again, the
origin is in the bottom left corner, and too large a scale can move
things out of view. Too small a scale turns everything into a dot.

@end(font)

@section(DrawDemoScaleY Scale Y Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(scale y)
@font(Times 14)
@bold(Scale Y Item)


This is the vertical scale to zoom in on the drawing. Again, the
origin is in the bottom left corner, and too large a scale can move
things out of view. Too small a scale turns everything into a dot.

@end(font)

@section(DrawDemoFlatness Flatness Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(flatness)
@font(Times 14)
@bold(Flatness Item)


This effects the tolerance used to draw curves (they are actually done
as line segments). Smaller numbers mean smoother curves, but more
segments (see vdrawSetFlat in the Galaxy documentation).

@end(font)

@section(DrawDemoLineWidth Line Width Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(line width)
@font(Times 14)
@bold(Line Width Item)


This is the width that the lines are drawn; it affects the outlines of
the object that are being drawn.

@end(font)

@section(DrawDemoMiterLimit Miter Limit Item)
@parent(DrawDemo)
@keyword(controls)
@keyword(miter limit)
@font(Times 14)
@bold(Miter Limit Item)


This controls the amount of a miter that is allowed for a line joints
(see vdrawSetMiterLimit in the Galaxy documentation).

@end(font)

@section(DrawDemoStartBtn Start Button)
@parent(DrawDemo)
@keyword(controls)
@keyword(start)
@font(Times 14)
@bold(Start Button)


This starts the draw demo again once it has been stopped to allow you
to set some of its controls. You can stop it by clicking in its
window.

@end(font)

@section(DrawDemoFontBtn Font Button)
@parent(DrawDemo)
@keyword(controls)
@keyword(font)
@font(Times 14)
@bold(Font Button)


This brings up the font chooser so you can set the font that the demo
uses when drawing text in the draw area.

@end(font)

@section(DrawDemoCloseBtn Close Button)
@parent(DrawDemo)
@keyword(controls)
@keyword(close)
@font(Times 14)
@bold(Close Button)


This quits the draw demo.

@end(font)

