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
        else
        {
            task.setTitle(processTitle(task.getTitle()));
        }
        if (task.getDescription() == null || task.getDescription().isEmpty())
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
        else
        {
            task.setTitle(processTitle(task.getTitle()));
        }
        if (task.getDescription() == null || task.getDescription().isEmpty())
        {
            task.setDescription("No description");
        }


        task.setID(id);


        return taskRepository.rewriteTask(task);
    }

    public Task updateTask(Long id, Task task)
    {
        task.setID(id);

        List<Task> tasks = taskRepository.getAllTasks();

        Task curr = tasks.get((int)(id - 1));

        if (task.getTitle() != null && !task.getTitle().isEmpty() && !curr.getTitle().equals(task.getTitle()))
        {
            curr.setTitle(processTitle(task.getTitle()));
        }

        if (task.getDescription() != null && !task.getDescription().isEmpty() && !curr.getDescription().equals(task.getDescription()))
        {
            curr.setDescription(task.getDescription());
        }

        if (task.getStatus() != null && !task.getStatus().isEmpty() && !curr.getStatus().equals(task.getStatus()))
        {
            if (!validateTaskStatus(task))
            {
                throw new IllegalArgumentException("the patched status is wrong");
            }

            curr.setStatus(task.getStatus());
        }

        return taskRepository.rewriteTask(curr);
    }




    private String processTitle(String title)
    {
        if (title.equals("No title"))
        {
            return title;
        }
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
