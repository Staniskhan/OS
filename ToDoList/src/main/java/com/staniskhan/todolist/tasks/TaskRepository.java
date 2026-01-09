package com.staniskhan.todolist.tasks;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Repository;
import tools.jackson.core.type.TypeReference;
import tools.jackson.databind.ObjectMapper;
import tools.jackson.databind.exc.MismatchedInputException;

import java.io.File;
import java.io.IOException;
import java.util.List;

@Repository
public class TaskRepository
{
    private File TASKS_FILE;
    private ObjectMapper objectMapper;

    public TaskRepository(@Value("${app.tasks.file.path}") String path)
    {
        objectMapper = new ObjectMapper();


        try
        {
            TASKS_FILE = new File(path);
            if (TASKS_FILE.createNewFile())
            {
                System.out.println("File tasks.json is created successfully");
            }
            else
            {
                System.out.println("File tasks.json already exists");
            }
        }
        catch (IOException e)
        {
            System.out.println("Error in opening/creating file tasks.json");
        }
    }

    public List<Task> getAllTasks()
    {
        try
        {
            return objectMapper.readValue(TASKS_FILE, new TypeReference<List<Task>>() {
            });
        }
        catch(MismatchedInputException e)
        {
            return null;
        }
    }

    public Task createTask(Task task)
    {
        List<Task> tasks = objectMapper.readValue(TASKS_FILE, new TypeReference<List<Task>>() {});
        task.setID((long)(tasks.size() + 1));
        tasks.add(task);
        objectMapper.writerWithDefaultPrettyPrinter().writeValue(TASKS_FILE, tasks);
        return task;
    }

    public Task getTaskByID(Long id)
    {
        List<Task> tasks = objectMapper.readValue(TASKS_FILE, new TypeReference<List<Task>>() {});
        return tasks.get((int)(id - 1));
    }

    public void deleteTaskByID(Long id)
    {
        List<Task> tasks = objectMapper.readValue(TASKS_FILE, new TypeReference<List<Task>>() {});
        tasks.remove((int)(id - 1));
        for (int i = (int)(id - 1); i < tasks.size(); i++)
        {
            Task curr = tasks.get(i);
            curr.setID((long)(i + 1));
            tasks.set(i, curr);
        }
        objectMapper.writerWithDefaultPrettyPrinter().writeValue(TASKS_FILE, tasks);
    }

    public Task rewriteTask(Task task)
    {
        List<Task> tasks = objectMapper.readValue(TASKS_FILE, new TypeReference<List<Task>>() {});
        tasks.set((int)(task.getID() - 1), task);
        objectMapper.writerWithDefaultPrettyPrinter().writeValue(TASKS_FILE, tasks);
        return task;
    }
}
