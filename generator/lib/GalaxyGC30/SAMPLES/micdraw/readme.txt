
the micdraw sample demonstrates the use of the domain manager for
building a draw program.  the sample also demonstrates how to
integrate DAS into an application.  when compiled with mdrawUSE_DAS
set to TRUE (the default value), the draw program will be "enabled"
with DAS.  this allows a drawing to be registered with the service
broker.  another user can then "connect" to the published drawing; the
two users can then work together on the document.  changes one makes
show up in the other's drawing in real time.

please note that the use of the undo manager in the micdraw sample is
not exhaustive.  for a more complete example of using the undo
manager, see the isniffer sample.
