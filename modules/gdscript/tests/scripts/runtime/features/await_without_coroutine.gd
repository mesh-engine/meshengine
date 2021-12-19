# https://github.com/meshengine/mesh/issues/50894

func test():
	print(await not_coroutine())


func not_coroutine():
	return "awaited"
