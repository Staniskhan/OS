package com.staniskhan.todolist.tasks;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;

import java.util.List;

@RestController
public class TaskController
{
    private final TaskService taskService;

    @Autowired
    public TaskController (TaskService taskService)
    {
        this.taskService = taskService;
    }

    @GetMapping("/tasks")
    @ResponseStatus(HttpStatus.OK)
    public List<Task> getAllTasks()
    {
        return taskService.getAllTasks();
    }

    @PostMapping("/tasks")
    @ResponseStatus(HttpStatus.CREATED)
    public Task createTask(@RequestBody Task task)
    {
        if (task.getID() != null)
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "ID must be empty when posting the task");
        }
        if ((task.getTitle() == null || task.getTitle().isEmpty()) &&
                (task.getDescription() == null || task.getDescription().isEmpty()))
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "The posted task is empty");
        }
        return taskService.createTask(task);
    }

    @GetMapping("tasks/{id}")
    @ResponseStatus(HttpStatus.OK)
    public Task getTask(@PathVariable("id") Long id)
    {
        try
        {
            return taskService.getTask(id);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }

    @DeleteMapping("tasks/{id}")
    @ResponseStatus(HttpStatus.OK)
    public void deleteTask(@PathVariable("id") Long id)
    {
        try
        {
            taskService.deleteTask(id);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }

    @PutMapping("tasks/{id}")
    @ResponseStatus(HttpStatus.OK)
    public Task rewriteTask(@PathVariable("id") Long id, @RequestBody Task task)
    {
        if (task.getID() != null)
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "ID must be empty when posting the task");
        }
        if ((task.getTitle() == null || task.getTitle().isEmpty()) &&
                (task.getDescription() == null || task.getDescription().isEmpty()))
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "The posted task is empty");
        }
        try
        {
            return taskService.rewriteTask(id, task);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }

    @PutMapping("/tasks")
    @ResponseStatus(HttpStatus.OK)
    public Task rewriteTask(@RequestBody Task task)
    {
        if (task.getID() == null)
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "ID is not defined");
        }
        if ((task.getTitle() == null || task.getTitle().isEmpty()) &&
                (task.getDescription() == null || task.getDescription().isEmpty()))
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "The posted task is empty");
        }
        try
        {
            return taskService.rewriteTask(task.getID(), task);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }

    @PatchMapping("tasks/{id}")
    @ResponseStatus(HttpStatus.OK)
    public Task updateTask(@PathVariable("id") Long id, @RequestBody Task task)
    {
        if (task.getID() != null)
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "You can't patch ID");
        }
        try
        {
            return taskService.updateTask(id, task);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }

    @PatchMapping("/tasks")
    @ResponseStatus(HttpStatus.OK)
    public Task updateTask(@RequestBody Task task)
    {
        if (task.getID() == null)
        {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "ID is not defined");
        }
        try
        {
            return taskService.updateTask(task.getID(), task);
        }
        catch(IndexOutOfBoundsException e)
        {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Request page does not exist");
        }
    }
}
