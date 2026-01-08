package com.staniskhan.todolist.tasks;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TaskService
{
    TaskRepository taskRepository;

    @Autowired
    public TaskService(TaskRepository taskRepository)
    {
        this.taskRepository = taskRepository;
    }

    public List<Task> getAllTasks()
    {
        return taskRepository.getAllTasks();
    }

    public Task createTask(Task task)
    {
        if (!validateTaskStatus(task))
        {
            throw new IllegalArgumentException("the status in posted task is wrong");
        }
        if (task.getStatus() == null || task.getStatus().isEmpty())
        {
            task.setStatus("todo");
        }
        if (task.getTitle() == null || task.getTitle().isEmpty())
        {
            task.setTitle("No title");
        }
        else if (task.getDescription() == null || task.getDescription().isEmpty())
        {
            task.setDescription("No description");
        }
        return taskRepository.createTask(task);
    }

    private boolean validateTaskStatus(Task task)
    {
        return task.getStatus() == null ||
                task.getStatus().isEmpty() ||
                task.getStatus().equals("todo") ||
                task.getStatus().equals("in_progress") ||
                task.getStatus().equals("done");
    }

    public Task getTask(Long id)
    {
        return taskRepository.findTaskByID(id);
    }
}
