name:
	\i+ (no spaces)

finding media/group:
	request: find name
	response: output of display(name, ...)

playing media:
	request: play name
	response: "Y" if played, "N" if not

finding objects with a common prefix:
	request: prefixed pattern
	response: name1 name2 ... nameN (possibly N=0)

