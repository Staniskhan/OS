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
        task.setTitle(processTitle(task.getTitle()));


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

    public Task getTask(Long id)
    {
        return taskRepository.getTaskByID(id);
    }

    public void deleteTask(Long id)
    {
        taskRepository.deleteTaskByID(id);
    }

    public Task rewriteTask(Long id, Task task)
    {
        task.setTitle(processTitle(task.getTitle()));


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


        task.setID(id);


        return taskRepository.rewriteTask(task);
    }




    private String processTitle(String title)
    {
        List<Task> tasks = taskRepository.getAllTasks();
        int count = 0;
        for (int i = 0; i < tasks.size(); i++) {
            boolean found = false;
            for (Task task : tasks) {
                if (task.getTitle().equals(title)) {
                    count++;
                    found = true;
                    break;
                }
            }
            if (!found) break;
            if (count > 1)
            {
                title = title.substring(0, title.length() - 2);
            }
            title += " " + count;
        }
        return title;
    }

    private boolean validateTaskStatus(Task task)
    {
        return task.getStatus() == null ||
                task.getStatus().isEmpty() ||
                task.getStatus().equals("todo") ||
                task.getStatus().equals("in_progress") ||
                task.getStatus().equals("done");
    }
}
