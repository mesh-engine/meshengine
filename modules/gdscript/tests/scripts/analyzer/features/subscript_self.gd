# https://github.com/meshengine/mesh/issues/43221
extends Node

func test():
	name = "Node"
	print(self["name"])
	self["name"] = "Changed"
	print(name)
